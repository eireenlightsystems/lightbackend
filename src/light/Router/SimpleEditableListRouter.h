#ifndef SIMPLEEDITABLELISTROUTER_H
#define SIMPLEEDITABLELISTROUTER_H

#include "SimpleEditableRouter.h"

#include <QHttpServer>

namespace light {

template <typename T>
class SimpleEditableListRouter : public SimpleEditableRouter<T>
{
public:
  constexpr static bool isContainer = true;
  SimpleEditableListRouter() = default;
  ~SimpleEditableListRouter() override = default;
  virtual QString getChildItemName() const = 0;
  virtual QHttpServerResponse getListItems(ID listId) = 0;

  void registerApi(QHttpServer& httpServer) const override {
    SimpleEditableRouter<T>::registerApi(httpServer);
    registerGetListItems(httpServer);
    registerDeleteItemFromList(httpServer);
    registerAddItemToList(httpServer);
  }

  virtual QHttpServerResponse postListItems(const QHttpServerRequest& req, ID listId) {
    JsonToIds converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto ids = converter.getIds();
    auto controller = this->createController();
    controller.addToList(listId, ids);
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  virtual QHttpServerResponse postListItem(ID listId, ID itemId) {
    auto controller = this->createController();
    controller.addToList(listId, {itemId});
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  virtual QHttpServerResponse delListItems(const QHttpServerRequest& req, ID listId) {
    JsonToIds converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto ids = converter.getIds();
    auto controller = this->createController();
    controller.delFromList(listId, ids);
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  virtual QHttpServerResponse delListItem(ID listId, ID itemId) {
    auto controller = this->createController();
    controller.delFromList(listId, {itemId});
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

protected:
  template <typename ChildType>
  QHttpServerResponse getListItemsHelper(ID listId, const QString& paramName) {
    const QVariantHash params{
	{paramName, listId},
    };

    Controller<ChildType, CRUD> controller;
    controller.setSession(this->getSession());
    auto objects = controller.sel(params);

    ToJsonConverter<ChildType> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

  QString getChildFullName(const QString& name) const {
    return QString("%1/<arg>/%2").arg(this->getFullName(), name);
  }

  QString getChildIdFullName(const QString& name) const {
    return getChildFullName(name) + "/" + "<arg>";
  }

private:
  void registerGetListItems(QHttpServer& httpServer) const {
    httpServer.route(getChildFullName(getChildItemName()),
		     QHttpServerRequest::Method::Get,
		     [](ID listId, const QHttpServerRequest& req) {
		       auto routeFunction = [listId](SessionShared session) {
			 RestRouter<T> router;
			 router.setSession(session);
			 return router.getListItems(listId);
		       };
		       return AbstractRestRouter::baseRouteFunction(routeFunction, req);
		     });
  }
  void registerDeleteItemFromList(QHttpServer& httpServer) const {
    httpServer.route(getChildIdFullName(getChildItemName()),
		     QHttpServerRequest::Method::Delete,
		     [](ID listId, ID itemId, const QHttpServerRequest& req) {
		       auto routeFunction = [listId, itemId](SessionShared session) {
			 RestRouter<T> router;
			 router.setSession(session);
			 return router.delListItem(listId, itemId);
		       };
		       return AbstractRestRouter::baseRouteFunction(routeFunction, req);
		     });

    httpServer.route(getChildFullName(getChildItemName()),
		     QHttpServerRequest::Method::Delete,
		     [](ID listId, const QHttpServerRequest& req) {
		       auto routeFunction = [listId](SessionShared session, const QHttpServerRequest& req) {
			 RestRouter<T> router;
			 router.setSession(session);
			 return router.delListItems(req, listId);
		       };
		       return AbstractRestRouter::baseRouteFunction(routeFunction, req, req);
		     });
  }
  void registerAddItemToList(QHttpServer& httpServer) const {
    httpServer.route(
	getChildIdFullName(getChildItemName()), QHttpServerRequest::Method::Post, [](ID listId, ID itemId, const QHttpServerRequest& req) {
	  auto routeFunction = [listId, itemId](SessionShared session) {
	    RestRouter<T> router;
	    router.setSession(session);
	    return router.postListItem(listId, itemId);
	  };
	  return AbstractRestRouter::baseRouteFunction(routeFunction, req);
	});

    httpServer.route(getChildFullName(getChildItemName()),
		     QHttpServerRequest::Method::Post,
		     [](ID listId, const QHttpServerRequest& req) {
		       auto routeFunction = [](SessionShared session, ID listId, const QHttpServerRequest& req) {
			 RestRouter<T> router;
			 router.setSession(session);
			 return router.postListItems(req, listId);
		       };
		       return AbstractRestRouter::baseRouteFunction(routeFunction, req, listId, req);
		     });
  }
};
} // namespace light

#endif // SIMPLEEDITABLELISTROUTER_H
