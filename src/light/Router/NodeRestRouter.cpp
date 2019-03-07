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

  Controller<Node, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto nodes = controller.sel(geopraphId, ownerId, nodeTypeId, contractId, gatewayId);

  NodeToJson converter;
  converter.convert(nodes);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

template <>
QHttpServerResponse RestRouter<Node>::post(const SessionShared& session, const QHttpServerRequest& req) const {
  JsonInsertParametersToNodeConverter converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Node, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.ins(parameters);

  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

template <>
QHttpServerResponse RestRouter<Node>::patch(const SessionShared& session, const QHttpServerRequest& req) const {
  JsonUpdateParametersToNodeConverter converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Node, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.upd(parameters);
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
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
  JsonNodeCoordinatesConverter converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Node, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.upd(parameters);
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

} // namespace light
