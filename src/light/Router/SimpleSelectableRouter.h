#ifndef SIMPLESELECTABLEROUTER_H
#define SIMPLESELECTABLEROUTER_H

#include "AbstractRestRouter.h"
#include "Controller.h"
#include "GatewayTypeDef.h"
#include "InternalServerErrorException.h"
#include "RestRouter.h"
#include "SessionOwner.h"
#include "ToJsonConverter.h"

#include <QHttpServerRequest>
#include <QHttpServerResponse>

namespace light {

template <typename T>
class SimpleSelectableRouter : public SessionOwner, public AbstractRestRouter
{
public:
  SimpleSelectableRouter() = default;
  ~SimpleSelectableRouter() override = default;
  void registerApi(QHttpServer& httpServer) const override {
    httpServer.route(getFullName(), QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
      auto routeFunction = [](SessionShared session, const QHttpServerRequest& req) {
	RestRouter<T> router;
	router.setSession(session);
	return router.get(req);
      };
      return AbstractRestRouter::baseRouteFunction(routeFunction, req, req);
    });

    httpServer.route(getIdFullName(), QHttpServerRequest::Method::Get, [](ID id, const QHttpServerRequest& req) {
      auto routeFunction = [](SessionShared session, ID id) {
	RestRouter<T> router;
	router.setSession(session);
	return router.get(id);
      };
      return AbstractRestRouter::baseRouteFunction(routeFunction, req, id);
    });
  }

  virtual QHttpServerResponse get(ID id) {
    auto controller = createController();
    auto objects = controller.sel(IDList{id});

    ToJsonConverter<T> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

  virtual QHttpServerResponse get(const QHttpServerRequest& req) {
    auto queryItems = parseUrlQuery(req.query());
    auto controller = createController();
    auto objects = controller.sel(queryItems);

    ToJsonConverter<T> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

protected:
  Controller<T, CRUD> createController() const {
    Controller<T, CRUD> controller;
    controller.setSession(getSession());
    return controller;
  }

  virtual QVariantHash parseUrlQuery(const QUrlQuery& urlQuery) const {
    QVariantHash params;
    for (const auto& item : urlQuery.queryItems()) {
      QVariant id = item.second.isEmpty() ? QVariant() : QVariant(item.second.toULongLong());
      params[item.first] = id;
    }
    return params;
  }
};

} // namespace light

#endif // SIMPLESELECTABLEROUTER_H
