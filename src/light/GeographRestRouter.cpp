#include "GeographRestRouter.h"

#include "Controller.h"
#include "GeographToJson.h"
#include "InternalServerErrorException.h"
#include "PostgresCrud.h"

namespace light {

QHttpServerResponse GeographRestRouter::get(const SessionShared& session, const QHttpServerRequest& req) {
  Q_UNUSED(req)

  Controller<Geograph, PostgresqlGateway::PostgresCrud> controller;
  controller.setSession(session);
  auto nodes = controller.sel();

  GeographToJson converter;
  converter.convert(nodes);
  if (!converter.getIdValid()) {
    throw InternalServerErrorException(converter.getErrorText());
  }
  QJsonDocument jsonDocument(converter.getJsonDocument());
  return QHttpServerResponse("text/json", jsonDocument.toJson());
}

} // namespace light
