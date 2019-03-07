#include "NodeTypeRestRouter.h"

#include "Controller.h"
#include "InternalServerErrorException.h"
#include "NodeType.h"
#include "NodeTypeToJson.h"
#include "PostgresCrud.h"

namespace light {

QHttpServerResponse NodeTypeRestRouter::get(const SessionShared& session, const QHttpServerRequest& req) {
  Q_UNUSED(req)

  Controller<NodeType, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto nodeTypes = controller.sel();

  NodeTypeToJson converter;
  converter.convert(nodeTypes);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

} // namespace light
