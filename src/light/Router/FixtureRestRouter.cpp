#include "FixtureRestRouter.h"

namespace light {

template <>
QString RestRouter<FixtureType>::getPath() const {
  return "/api2/fixture/type";
}

template <>
QList<QHttpServerRequest::Method> RestRouter<FixtureType>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

template <>
QHttpServerResponse RestRouter<FixtureType>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<FixtureType>(session);
}

template <>
QString RestRouter<FixtureHeightType>::getPath() const {
  return "/api2/fixture/heightType";
}

template <>
QList<QHttpServerRequest::Method> RestRouter<FixtureHeightType>::getAsseccibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

template <>
QHttpServerResponse RestRouter<FixtureHeightType>::get(const SessionShared& session,
						       const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<FixtureHeightType>(session);
}

} // namespace light
