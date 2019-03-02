#include "NodeRestRouter.h"

#include "Controller.h"
#include "InternalServerErrorException.h"
#include "NodeToJson.h"
#include "PostgresCrud.h"

namespace light {

QList<AbstractRestRouter::ApiItem> NodeRestRouter::getApiItems() {
  const QString route("/node");
  return {
      {route,
       QHttpServerRequest::Method::Get,
       [](const SessionShared& session, const QHttpServerRequest& req) { return NodeRestRouter::get(session, req); }},
      {route,
       QHttpServerRequest::Method::Post,
       [](const SessionShared& session, const QHttpServerRequest& req) { return NodeRestRouter::post(session, req); }},
      {route,
       QHttpServerRequest::Method::Patch,
       [](const SessionShared& session, const QHttpServerRequest& req) { return NodeRestRouter::patch(session, req); }},
  };
}

QHttpServerResponse NodeRestRouter::get(const SessionShared& session, const QHttpServerRequest& req) {
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

QHttpServerResponse NodeRestRouter::post(const SessionShared& session, const QHttpServerRequest& req) {
  Controller<Node, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  //  controller.ins();

  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

QHttpServerResponse NodeRestRouter::patch(const SessionShared& session, const QHttpServerRequest& req) {
  Controller<Node, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  //  controller.upd();
  return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
}

} // namespace light
