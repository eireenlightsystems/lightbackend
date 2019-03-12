#ifndef TEMPLATEROUTER_H
#define TEMPLATEROUTER_H

#include "AbstractRestRouter.h"

namespace light {

template <typename T>
class RestRouter;

template <typename T>
class TemplateRouter : public AbstractRestRouter
{
public:
  TemplateRouter() = default;
  ~TemplateRouter() override = default;
  void registerApi(QHttpServer& httpServer) const override;

private:
  void registerGet(QHttpServer& httpServer) const;
  void registerPost(QHttpServer& httpServer) const;
  void registerPatch(QHttpServer& httpServer) const;
  void registerDelete(QHttpServer& httpServer) const;
  void registerDeleteItemFromList(QHttpServer& httpServer) const;
  void registerAddItemToList(QHttpServer& httpServer) const;
};

template <typename T>
void TemplateRouter<T>::registerApi(QHttpServer& httpServer) const {
  registerGet(httpServer);
  registerPost(httpServer);
  registerPatch(httpServer);
  registerDelete(httpServer);
  registerDeleteItemFromList(httpServer);
  registerAddItemToList(httpServer);
}

template <typename T>
void TemplateRouter<T>::registerGet(QHttpServer& httpServer) const {
  httpServer.route(RestRouter<T>::path, QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      RestRouter<T> router;
      return router.get(session, req);
    };
    return baseRouteFunction(routeFunction, req);
  });
}

template <typename T>
void TemplateRouter<T>::registerPost(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isEditable) {
    httpServer.route(RestRouter<T>::path, QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.post(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerPatch(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isEditable) {
    httpServer.route(RestRouter<T>::path, QHttpServerRequest::Method::Patch, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.patch(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerDelete(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isEditable) {
    httpServer.route(RestRouter<T>::path, QHttpServerRequest::Method::Delete, [](const QHttpServerRequest& req) {
      auto routeFunction = [](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.del(session, req);
      };
      return baseRouteFunction(routeFunction, req);
    });

    const QString deleteByIdPath = QString("%1/<arg>").arg(RestRouter<T>::path);
    httpServer.route(deleteByIdPath, QHttpServerRequest::Method::Delete, [](ID id) {
      auto routeFunction = [](ID id) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.delById(session, id);
      };
      return baseRouteFunction(routeFunction, id);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerDeleteItemFromList(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isList) {
    const QString deleteItemPath = QString("%1/<arg>/item/<arg>").arg(RestRouter<T>::path);
    httpServer.route(deleteItemPath, QHttpServerRequest::Method::Delete, [](ID listId, ID itemId) {
      auto routeFunction = [listId, itemId]() {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.delItemFromList(session, listId, itemId);
      };
      return baseRouteFunction(routeFunction);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerAddItemToList(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isList) {
    const QString addItemPath = QString("%1/<arg>/item/<arg>").arg(RestRouter<T>::path);
    httpServer.route(addItemPath, QHttpServerRequest::Method::Post, [](ID listId, ID itemId) {
      auto routeFunction = [listId, itemId]() {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	return router.addItemToList(session, listId, itemId);
      };
      return baseRouteFunction(routeFunction);
    });
  }
}

} // namespace light

#endif // TEMPLATEROUTER_H
