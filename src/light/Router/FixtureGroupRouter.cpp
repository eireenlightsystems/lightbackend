#include "FixtureGroupRouter.h"

#include "FixtureGroupController.h"

namespace light {

template <>
QString RestRouter<FixtureGroup>::getPath() const {
  return "/api2/fixture-group";
}

template <>
QHttpServerResponse RestRouter<FixtureGroup>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  const auto urlQuery = req.query();
  ID ownerId = urlQuery.queryItemValue("ownerId").toULongLong();
  ID typeId = urlQuery.queryItemValue("typeId").toULongLong();
  return selSimple<FixtureGroup>(session, ownerId, typeId);
}

template <>
QHttpServerResponse RestRouter<FixtureGroup>::post(const SessionShared& session, const QHttpServerRequest& req) const {
  return postSimple<FixtureGroup, FixtureGroupInsertParameters>(session, req);
}

template <>
QHttpServerResponse RestRouter<FixtureGroup>::patch(const SessionShared& session, const QHttpServerRequest& req) const {
  return patchSimple<FixtureGroup, FixtureGroupUpdateParameters>(session, req);
}

template <>
QHttpServerResponse RestRouter<FixtureGroup>::del(const SessionShared& session, const QHttpServerRequest& req) const {
  return delSimple<FixtureGroup>(session, req);
}

template<>
QString RestRouter<FixtureGroupType>::getPath() const {
  return "/api2/fixture-group-type";
}

template<>
QHttpServerResponse RestRouter<FixtureGroupType>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<FixtureGroupType>(session);
}

template<>
QString RestRouter<FixtureGroupOwner>::getPath() const {
  return "/api2/fixture-group-owner";
}

template<>
QHttpServerResponse RestRouter<FixtureGroupOwner>::get(const SessionShared& session, const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return selSimple<Contragent>(session);
}

} // namespace light
