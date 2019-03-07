#include "GeographRestRouter.h"

#include "Controller.h"
#include "GeographToJson.h"
#include "InternalServerErrorException.h"
#include "PostgresCrud.h"

namespace light {

template <>
QString RestRouter<Geograph>::getPath() const {
  return "/api2/geograph";
}

template <>
QHttpServerResponse RestRouter<Geograph>::get(const SessionShared& session, const QHttpServerRequest& req) const {
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

template <>
QList<QHttpServerRequest::Method> RestRouter<Geograph>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

} // namespace light
