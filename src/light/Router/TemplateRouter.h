#ifndef TEMPLATEROUTER_H
#define TEMPLATEROUTER_H

#include "AbstractRestRouter.h"
#include "RestRouter.h"

namespace light {

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

private:
  const QString routerPrefixString = "/api/v1/";
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
  httpServer.route(
      routerPrefixString + RestRouter<T>::path, QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
	auto routeFunction = [](const QHttpServerRequest& req) {
	  auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	  RestRouter<T> router;
	  router.setSession(session);
	  return router.get(req);
	};
	return baseRouteFunction(routeFunction, req);
      });

  const QString getById = routerPrefixString + QString("%1/<arg>").arg(RestRouter<T>::path);
  httpServer.route(getById, QHttpServerRequest::Method::Get, [](ID id) {
    auto routeFunction = [](ID id) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      RestRouter<T> router;
      router.setSession(session);
      return router.get(id);
    };
    return baseRouteFunction(routeFunction, id);
  });
}

template <typename T>
void TemplateRouter<T>::registerPost(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isEditable) {
    httpServer.route(
	routerPrefixString + RestRouter<T>::path, QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
	  auto routeFunction = [](const QHttpServerRequest& req) {
	    auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	    RestRouter<T> router;
	    router.setSession(session);
	    return router.post(req);
	  };
	  return baseRouteFunction(routeFunction, req);
	});
  }
}

template <typename T>
void TemplateRouter<T>::registerPatch(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isEditable) {
    httpServer.route(
	routerPrefixString + RestRouter<T>::path, QHttpServerRequest::Method::Patch, [](const QHttpServerRequest& req) {
	  auto routeFunction = [](const QHttpServerRequest& req) {
	    auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	    RestRouter<T> router;
	    router.setSession(session);
	    return router.patch(req);
	  };
	  return baseRouteFunction(routeFunction, req);
	});

    const QString patchById = routerPrefixString + QString("%1/<arg>").arg(RestRouter<T>::path);
    httpServer.route(patchById, QHttpServerRequest::Method::Patch, [](ID id, const QHttpServerRequest& req) {
      auto routeFunction = [](ID id, const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	router.setSession(session);
	return router.patch(req, id);
      };
      return baseRouteFunction(routeFunction, id, req);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerDelete(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isEditable) {
    httpServer.route(routerPrefixString + RestRouter<T>::path,
		     QHttpServerRequest::Method::Delete,
		     [](const QHttpServerRequest& req) {
		       auto routeFunction = [](const QHttpServerRequest& req) {
			 auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
			 RestRouter<T> router;
			 router.setSession(session);
			 return router.del(req);
		       };
		       return baseRouteFunction(routeFunction, req);
		     });

    const QString deleteByIdPath = routerPrefixString + QString("%1/<arg>").arg(RestRouter<T>::path);
    httpServer.route(deleteByIdPath, QHttpServerRequest::Method::Delete, [](ID id) {
      auto routeFunction = [](ID id) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	router.setSession(session);
	return router.delById(id);
      };
      return baseRouteFunction(routeFunction, id);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerDeleteItemFromList(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isList) {
    const QString deleteItemPath = routerPrefixString + QString("%1/<arg>/item/<arg>").arg(RestRouter<T>::path);
    httpServer.route(deleteItemPath, QHttpServerRequest::Method::Delete, [](ID listId, ID itemId) {
      auto routeFunction = [listId, itemId]() {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	router.setSession(session);
	return router.delListItem(listId, itemId);
      };
      return baseRouteFunction(routeFunction);
    });

    const QString deleteItemsPath = routerPrefixString + QString("%1/<arg>/item").arg(RestRouter<T>::path);
    httpServer.route(deleteItemsPath, QHttpServerRequest::Method::Delete, [](ID listId, const QHttpServerRequest& req) {
      auto routeFunction = [listId](const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	router.setSession(session);
	return router.delListItems(req, listId);
      };
      return baseRouteFunction(routeFunction, req);
    });
  }
}

template <typename T>
void TemplateRouter<T>::registerAddItemToList(QHttpServer& httpServer) const {
  if constexpr (RestRouter<T>::isList) {
    const QString addItemPath = routerPrefixString + QString("%1/<arg>/item/<arg>").arg(RestRouter<T>::path);
    httpServer.route(addItemPath, QHttpServerRequest::Method::Post, [](ID listId, ID itemId) {
      auto routeFunction = [listId, itemId]() {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	router.setSession(session);
	return router.postListItem(listId, itemId);
      };
      return baseRouteFunction(routeFunction);
    });

    const QString addItemsPath = routerPrefixString + QString("%1/<arg>/item").arg(RestRouter<T>::path);
    httpServer.route(addItemsPath, QHttpServerRequest::Method::Post, [](ID listId, const QHttpServerRequest& req) {
      auto routeFunction = [](ID listId, const QHttpServerRequest& req) {
	auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
	RestRouter<T> router;
	router.setSession(session);
	return router.postListItems(req, listId);
      };
      return baseRouteFunction(routeFunction, listId, req);
    });
  }
}

} // namespace light

#endif // TEMPLATEROUTER_H
