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

template<>
QString RestRouter<Gateway>::getPath() const {
  return "/api2/gateway";
}

template <>
QHttpServerResponse RestRouter<Gateway>::get(const SessionShared& session, const QHttpServerRequest& req) const {
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

template <>
QHttpServerResponse RestRouter<Gateway>::post(const SessionShared& session, const QHttpServerRequest& req) const {
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

template <>
QHttpServerResponse RestRouter<Gateway>::patch(const SessionShared& session, const QHttpServerRequest& req) const {
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

template<>
QHttpServerResponse RestRouter<Gateway>::del(const SessionShared& session, const QHttpServerRequest& req) const {
  return delSimple<Gateway>(session, req);
}

template<>
QString RestRouter<EquipmentOwner>::getPath() const {
  return "/api2/gateway/owner";
}

template <>
QHttpServerResponse RestRouter<EquipmentOwner>::get(const SessionShared& session, const QHttpServerRequest& req) const {
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

template <>
QList<QHttpServerRequest::Method> RestRouter<EquipmentOwner>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

template<>
QString RestRouter<GatewayType>::getPath() const {
  return "/api2/gateway/type";
}

template <>
QHttpServerResponse RestRouter<GatewayType>::get(const SessionShared& session, const QHttpServerRequest& req) const {
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

template <>
QList<QHttpServerRequest::Method> RestRouter<GatewayType>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

} // namespace light
