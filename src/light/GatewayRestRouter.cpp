#include "GatewayRestRouter.h"

#include "BadRequestException.h"
#include "Controller.h"
#include "EquipmentOwner.h"
#include "GatewayOwnerToJson.h"
#include "GatewayToJson.h"
#include "GatewayTypeToJson.h"
#include "HttpServerConverters.h"
#include "InternalServerErrorException.h"
#include "JsonToGatewayConverter.h"
#include "PostgresCrud.h"

#include <QHttpServerRequest>

namespace light {

QHttpServerResponse GatewayRestRouter::get(const SessionShared& session, const QHttpServerRequest& req) {
  const auto urlQuery = req.query();
  ID geopraphId = urlQuery.queryItemValue("geographId").toULongLong();
  ID ownerId = urlQuery.queryItemValue("ownerId").toULongLong();
  ID gatewayTypeId = urlQuery.queryItemValue("gatewayTypeId").toULongLong();
  ID contractId = urlQuery.queryItemValue("contractId").toULongLong();
  ID nodeId = urlQuery.queryItemValue("nodeId").toULongLong();

  Controller<Gateway, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto gateways = controller.sel(geopraphId, ownerId, gatewayTypeId, contractId, nodeId);

  GatewayToJson converter;
  converter.convert(gateways);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

QHttpServerResponse GatewayRestRouter::post(const SessionShared& session, const QHttpServerRequest& req) {
  JsonInsertParametersToGatewayConverter converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Gateway, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.ins(parameters);
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

QHttpServerResponse GatewayRestRouter::patch(const SessionShared& session, const QHttpServerRequest& req) {
  JsonUpdateParametersToGatewayConverter converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto parameters = converter.getParameters();

  Controller<Gateway, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.upd(parameters);
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

QHttpServerResponse GatewayRestRouter::del(const SessionShared &session, const QHttpServerRequest &req)
{
  JsonToIds converter;
  converter.convert(req.body());
  if (!converter.getIdValid()) {
    throw BadRequestException(converter.getErrorText());
  }
  auto ids = converter.getIds();
  Controller<Gateway, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  controller.del(ids);
  return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
}

QHttpServerResponse GatewayRestRouter::getOwner(const SessionShared& session, const QHttpServerRequest& req) {
  Q_UNUSED(req)

  Controller<EquipmentOwner, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto owners = controller.sel();

  GatewayOwnerToJson converter;
  converter.convert(owners);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

QHttpServerResponse GatewayRestRouter::getTypes(const SessionShared& session, const QHttpServerRequest& req) {
  Q_UNUSED(req)

  Controller<GatewayType, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto gatewayTypes = controller.sel();

  GatewayTypeToJson converter;
  converter.convert(gatewayTypes);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

} // namespace light
