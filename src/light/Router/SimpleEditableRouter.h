#ifndef SIMPLEEDITABLEROUTER_H
#define SIMPLEEDITABLEROUTER_H

#include "BadRequestException.h"
#include "Controller.h"
#include "JsonToIds.h"
#include "SimpleSelectableRouter.h"

#include <QHttpServerRequest>
#include <QHttpServerResponse>

namespace light {

template <typename T>
class SimpleEditableRouter : public SimpleSelectableRouter<T>
{
public:
  SimpleEditableRouter() = default;
  ~SimpleEditableRouter() override = default;
  void registerApi(QHttpServer& httpServer) const override {
    SimpleSelectableRouter<T>::registerApi(httpServer);
    registerPost(httpServer);
    registerPatch(httpServer);
    registerDelete(httpServer);
  }

  virtual QHttpServerResponse post(const QHttpServerRequest& req) const {
    auto controller = this->createController();
    const auto params = fromBody(req.body());
    const IDList idList = controller.ins(params);
    QString result;
    if (idList.count() > 1) {
      QStringList idsString;
      std::transform(
	  idList.begin(), idList.end(), std::back_inserter(idsString), [](ID id) { return QString::number(id); });
      result = "[" + idsString.join(",") + "]";
    } else {
      result = QString::number(idList.first());
    }
    return QHttpServerResponse(result);
  }

  virtual QHttpServerResponse patch(const QHttpServerRequest& req) const {
    auto controller = this->createController();
    const auto params = fromBody(req.body());
    controller.upd(params);
    return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
  }

  virtual QHttpServerResponse patch(const QHttpServerRequest& req, ID id) const {
    auto controller = this->createController();
    const auto params = fromBody(req.body());
    controller.upd(id, params.first());
    return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
  }

  virtual QHttpServerResponse del(const QHttpServerRequest& req) const {
    JsonToIds converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto ids = converter.getIds();
    return delList(ids);
  }

  virtual QHttpServerResponse delById(ID id) const {
    return delList({id});
  }

protected:
  QHttpServerResponse delList(const IDList& ids) const {
    auto controller = this->createController();
    controller.del(ids);
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  QList<QVariantHash> fromBody(const QByteArray& data) const {
    QJsonParseError parseError;
    QJsonDocument jDoc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
      qDebug() << parseError.errorString();
      throw BadRequestException(parseError.errorString());
    }

    QJsonArray array;
    if (jDoc.isObject()) {
      array << jDoc.object();
    } else if (jDoc.isArray()) {
      array = jDoc.array();
    } else {
      throw BadRequestException("Ошибка разбора тела запроса");
    }

    QList<QVariantHash> result;
    for (const auto value : array) {
      auto object = value.toObject();
      result << object.toVariantHash();
    }

    return result;
  }

private:
  void registerPost(QHttpServer& httpServer) const {
    httpServer.route(this->getFullName(), QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
      auto routeFunction = [](SessionShared session, const QHttpServerRequest& req) {
	RestRouter<T> router;
	router.setSession(session);
	return router.post(req);
      };
      return AbstractRestRouter::baseRouteFunction(routeFunction, req, req);
    });
  }
  void registerPatch(QHttpServer& httpServer) const {
    httpServer.route(this->getFullName(), QHttpServerRequest::Method::Patch, [](const QHttpServerRequest& req) {
      auto routeFunction = [](SessionShared session, const QHttpServerRequest& req) {
	RestRouter<T> router;
	router.setSession(session);
	return router.patch(req);
      };
      return AbstractRestRouter::baseRouteFunction(routeFunction, req, req);
    });

    httpServer.route(
	this->getIdFullName(), QHttpServerRequest::Method::Patch, [](ID id, const QHttpServerRequest& req) {
	  auto routeFunction = [](SessionShared session, ID id, const QHttpServerRequest& req) {
	    RestRouter<T> router;
	    router.setSession(session);
	    return router.patch(req, id);
	  };
	  return AbstractRestRouter::baseRouteFunction(routeFunction, req, id, req);
	});
  }
  void registerDelete(QHttpServer& httpServer) const {
    httpServer.route(this->getFullName(), QHttpServerRequest::Method::Delete, [](const QHttpServerRequest& req) {
      auto routeFunction = [](SessionShared session, const QHttpServerRequest& req) {
	RestRouter<T> router;
	router.setSession(session);
	return router.del(req);
      };
      return AbstractRestRouter::baseRouteFunction(routeFunction, req, req);
    });

    httpServer.route(this->getIdFullName(), QHttpServerRequest::Method::Delete, [](ID id, const QHttpServerRequest& req) {
      auto routeFunction = [](SessionShared session, ID id) {
	RestRouter<T> router;
	router.setSession(session);
	return router.delById(id);
      };
      return AbstractRestRouter::baseRouteFunction(routeFunction, req, id);
    });
  }
};

} // namespace light

#endif // SIMPLEEDITABLEROUTER_H
