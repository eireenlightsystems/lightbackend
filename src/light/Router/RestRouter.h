#ifndef RESTROUTER_H
#define RESTROUTER_H

#include "AbstractRestRouter.h"
#include "BadRequestException.h"
#include "Controller.h"
#include "FromJsonConverter.h"
#include "HttpServerConverters.h"
#include "NotImplementedException.h"
#include "PostgresCrud.h"
#include "ToJsonConverter.h"
#include "InternalServerErrorException.h"

namespace light {

template <typename T>
class RestRouter : public AbstractRestRouter
{
public:
  RestRouter() = default;

  QHttpServerResponse get(const SessionShared& session, const QHttpServerRequest& req) const override;
  QHttpServerResponse post(const SessionShared& session, const QHttpServerRequest& req) const override;
  QHttpServerResponse patch(const SessionShared& session, const QHttpServerRequest& req) const override;
  QHttpServerResponse del(const SessionShared& session, const QHttpServerRequest& req) const override;
  void registerApi(QHttpServer& httpServer) const override;
  QString getPath() const override;

protected:
  QList<QHttpServerRequest::Method> getAccessibleMethods() const;
};

template <typename T>
QHttpServerResponse RestRouter<T>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(session)
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

template <typename T>
QHttpServerResponse RestRouter<T>::post(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(session)
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

template <typename T>
QHttpServerResponse RestRouter<T>::patch(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(session)
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

template <typename T>
QHttpServerResponse RestRouter<T>::del(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(session)
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

template <typename T>
void RestRouter<T>::registerApi(QHttpServer& httpServer) const {
  QList<QHttpServerRequest::Method> accessibleMethods = getAccessibleMethods();
  if (accessibleMethods.contains(QHttpServerRequest::Method::Get)) {
    httpServer.route(getPath(), QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.get(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }

  if (accessibleMethods.contains(QHttpServerRequest::Method::Post)) {
    httpServer.route(getPath(), QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.post(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }

  if (accessibleMethods.contains(QHttpServerRequest::Method::Patch)) {
    httpServer.route(getPath(), QHttpServerRequest::Method::Patch, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.patch(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }

  if (accessibleMethods.contains(QHttpServerRequest::Method::Delete)) {
    httpServer.route(getPath(), QHttpServerRequest::Method::Delete, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.del(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }
}

template <typename T>
QList<QHttpServerRequest::Method> RestRouter<T>::getAccessibleMethods() const {
  return {QHttpServerRequest::Method::Get,
	  QHttpServerRequest::Method::Post,
	  QHttpServerRequest::Method::Patch,
	  QHttpServerRequest::Method::Delete};
}

template <typename Object, typename... Args>
QHttpServerResponse selSimple(const SessionShared& session, Args&&... args) {
  Controller<Object, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto gateways = controller.sel(std::forward<Args>(args)...);

  ToJsonConverter<Object> converter;
  converter.convert(gateways);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

template <typename Object, typename InsertPatameter>
QHttpServerResponse postSimple(const SessionShared& session, const QHttpServerRequest& req) {
  FromJsonConverter<InsertPatameter> converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Object, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.ins(parameters);
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

template <typename Object, typename UpdatePatameter>
QHttpServerResponse patchSimple(const SessionShared& session, const QHttpServerRequest& req) {
  FromJsonConverter<UpdatePatameter> converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Object, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.upd(parameters);
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

template <typename T>
QHttpServerResponse delSimple(const SessionShared& session, const QHttpServerRequest& req) {
  JsonToIds converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto ids = converter.getIds();
  Controller<T, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.del(ids);
  return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
}

} // namespace light

#endif // RESTROUTER_H
