#include "NodeTypeRestRouter.h"

#include "Controller.h"
#include "InternalServerErrorException.h"
#include "NodeType.h"
#include "NodeTypeToJson.h"
#include "PostgresCrud.h"

namespace light {

template <>
QString RestRouter<NodeType>::getPath() const {
  return "/api2/nodeType";
}

template <>
QHttpServerResponse RestRouter<NodeType>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(req)

  return selSimple<NodeType>(session);
}

template <>
QList<QHttpServerRequest::Method> RestRouter<NodeType>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

} // namespace light
