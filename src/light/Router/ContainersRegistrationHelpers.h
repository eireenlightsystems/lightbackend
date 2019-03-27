#ifndef CONTAINERSREGISTRATIONHELPERS_H
#define CONTAINERSREGISTRATIONHELPERS_H

#define RegisterGetHelper(ClassName, Name, GetMethod)                                                       \
  httpServer.route(                                                                                         \
      QString("%1/<arg>/%2").arg(this->getFullName(), Name), QHttpServerRequest::Method::Get, [](ID listId) { \
	auto routeFunction = [listId](SessionShared session) {                                              \
	  RestRouter<ClassName> router;                                                                     \
	  router.setSession(session);                                                                       \
	  return router.GetMethod(listId);                                                                  \
	};                                                                                                  \
	return AbstractRestRouter::baseRouteFunction(routeFunction);                                        \
      });

#define RegisterAddOneItemHelper(ClassName, Name, AddMethod)                        \
  httpServer.route(QString("%1/<arg>/%2/<arg>").arg(this->getFullName(), Name),     \
		   QHttpServerRequest::Method::Post,                                \
		   [](ID listId, ID itemId) {                                       \
		     auto routeFunction = [listId, itemId](SessionShared session) { \
		       RestRouter<ClassName> router;                                \
		       router.setSession(session);                                  \
		       return router.AddMethod(listId, itemId);                     \
		     };                                                             \
		     return AbstractRestRouter::baseRouteFunction(routeFunction);   \
		   });

#define RegisterAddItemsHelper(ClassName, Name, AddMethod)                                                      \
  httpServer.route(QString("%1/<arg>/%2").arg(this->getFullName(), Name),                                       \
		   QHttpServerRequest::Method::Post,                                                            \
		   [](ID listId, const QHttpServerRequest& req) {                                               \
		     auto routeFunction = [](SessionShared session, ID listId, const QHttpServerRequest& req) { \
		       RestRouter<ClassName> router;                                                            \
		       router.setSession(session);                                                              \
		       return router.AddMethod(req, listId);                                                    \
		     };                                                                                         \
		     return AbstractRestRouter::baseRouteFunction(routeFunction, listId, req);                  \
		   });

#define RegisterDeleteOneItemHelper(ClassName, Name, DeleteMethod)                  \
  httpServer.route(QString("%1/<arg>/%2/<arg>").arg(this->getFullName(), Name),     \
		   QHttpServerRequest::Method::Delete,                              \
		   [](ID listId, ID itemId) {                                       \
		     auto routeFunction = [listId, itemId](SessionShared session) { \
		       RestRouter<ClassName> router;                                \
		       router.setSession(session);                                  \
		       return router.DeleteMethod(listId, itemId);                  \
		     };                                                             \
		     return AbstractRestRouter::baseRouteFunction(routeFunction);   \
		   });

#define RegisterDeleteItemsHelper(ClassName, Name, DeleteMethod)                                           \
  httpServer.route(QString("%1/<arg>/%2").arg(this->getFullName(), Name),                                  \
		   QHttpServerRequest::Method::Delete,                                                     \
		   [](ID listId, const QHttpServerRequest& req) {                                          \
		     auto routeFunction = [listId](SessionShared session, const QHttpServerRequest& req) { \
		       RestRouter<ClassName> router;                                                       \
		       router.setSession(session);                                                         \
		       return router.DeleteMethod(req, listId);                                            \
		     };                                                                                    \
		     return AbstractRestRouter::baseRouteFunction(routeFunction, req);                     \
		   });

#endif // CONTAINERSREGISTRATIONHELPERS_H
