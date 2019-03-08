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

  return selSimple<Geograph>(session);
}

template <>
QList<QHttpServerRequest::Method> RestRouter<Geograph>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

} // namespace light
