#include "FixtureRestRouter.h"

#include "FixtureController.h"

namespace light {

template <>
QString RestRouter<Fixture>::getPath() const {
  return "/api2/fixture";
}

template <>
QHttpServerResponse RestRouter<Fixture>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  const auto urlQuery = req.query();
  ID geopraphId = urlQuery.queryItemValue("geographId").toULongLong();
  ID ownerId = urlQuery.queryItemValue("ownerId").toULongLong();
  ID fixtureTypeId = urlQuery.queryItemValue("fixtureTypeId").toULongLong();
  ID substationId = urlQuery.queryItemValue("substationId").toULongLong();
  ID modeId = urlQuery.queryItemValue("modeId").toULongLong();
  ID contractId = urlQuery.queryItemValue("contractId").toULongLong();
  ID nodeId = urlQuery.queryItemValue("nodeId").toULongLong();
  return selSimple<Fixture>(session, geopraphId, ownerId, fixtureTypeId, substationId, modeId, contractId, nodeId);
}

template <>
QHttpServerResponse RestRouter<Fixture>::post(const SessionShared& session, const QHttpServerRequest& req) const {
  return postSimple<Fixture, FixtureInsertParameters>(session, req);
}

template <>
QHttpServerResponse RestRouter<Fixture>::patch(const SessionShared& session, const QHttpServerRequest& req) const {
  return patchSimple<Fixture, FixtureUpdateParameters>(session, req);
}

template <>
QHttpServerResponse RestRouter<Fixture>::del(const SessionShared& session, const QHttpServerRequest& req) const {
  return delSimple<Fixture>(session, req);
}

template <>
QHttpServerResponse RestRouter<Fixture>::delById(const SessionShared& session, ID id) const {
  return delByIds<Fixture>(session, {id});
}

template <>
QString RestRouter<FixtureType>::getPath() const {
  return "/api2/fixture-type";
}

template <>
QList<QHttpServerRequest::Method> RestRouter<FixtureType>::getAccessibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

template <>
QHttpServerResponse RestRouter<FixtureType>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<FixtureType>(session);
}

template <>
QString RestRouter<FixtureHeightType>::getPath() const {
  return "/api2/fixture-height-type";
}

template <>
QList<QHttpServerRequest::Method> RestRouter<FixtureHeightType>::getAccessibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

template <>
QHttpServerResponse RestRouter<FixtureHeightType>::get(const SessionShared& session,
						       const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<FixtureHeightType>(session);
}

template <>
QString RestRouter<Substation>::getPath() const {
  return "/api2/substation";
}

template <>
QList<QHttpServerRequest::Method> RestRouter<Substation>::getAccessibleMethods() const {
  return {QHttpServerRequest::Method::Get};
}

template <>
QHttpServerResponse RestRouter<Substation>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<Substation>(session);
}

} // namespace light
