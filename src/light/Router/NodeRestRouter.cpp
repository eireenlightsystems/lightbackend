#include "NodeRestRouter.h"

#include "BadRequestException.h"
#include "Controller.h"
#include "HttpServerConverters.h"
#include "InternalServerErrorException.h"
#include "JsonToNodeConverter.h"
#include "NodeController.h"
#include "NodeToJson.h"
#include "PostgresCrud.h"

#include <QGeoCoordinate>

namespace light {

template <>
QString RestRouter<Node>::getPath() const {
  return "/api2/node";
}

template <>
QHttpServerResponse RestRouter<Node>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  const auto urlQuery = req.query();
  ID geopraphId = urlQuery.queryItemValue("geographId").toULongLong();
  ID ownerId = urlQuery.queryItemValue("ownerId").toULongLong();
  ID nodeTypeId = urlQuery.queryItemValue("nodeTypeId").toULongLong();
  ID contractId = urlQuery.queryItemValue("contractId").toULongLong();
  ID gatewayId = urlQuery.queryItemValue("gatewayId").toULongLong();

  return selSimple<Node>(session, geopraphId, ownerId, nodeTypeId, contractId, gatewayId);
}

template <>
QHttpServerResponse RestRouter<Node>::post(const SessionShared& session, const QHttpServerRequest& req) const {
  return postSimple<Node, NodeInsertParameters>(session, req);
}

template <>
QHttpServerResponse RestRouter<Node>::patch(const SessionShared& session, const QHttpServerRequest& req) const {
  return patchSimple<Node, NodeUpdateParameters>(session, req);
}

template <>
QHttpServerResponse RestRouter<Node>::del(const SessionShared& session, const QHttpServerRequest& req) const {
  return delSimple<Node>(session, req);
}

template <>
QString RestRouter<NodeCoordinate>::getPath() const {
  return "/api2/node/coordinate";
}

template <>
QHttpServerResponse RestRouter<NodeCoordinate>::patch(const SessionShared& session,
						      const QHttpServerRequest& req) const {
  return patchSimple<Node, NodeCoordinateParameters>(session, req);
}

} // namespace light
