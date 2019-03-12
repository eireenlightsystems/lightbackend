#ifndef FIXTUREGROUPROUTER_H
#define FIXTUREGROUPROUTER_H

#include "RestRouter.h"

namespace light {

template <>
QString RestRouter<FixtureGroup>::getPath() const;

template <>
QHttpServerResponse RestRouter<FixtureGroup>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<FixtureGroup>::post(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<FixtureGroup>::patch(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<FixtureGroup>::del(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QHttpServerResponse RestRouter<FixtureGroup>::delById(const SessionShared& session, ID id) const;

template <>
QHttpServerResponse RestRouter<FixtureGroup>::delItemFromList(const SessionShared& session,
							      ID listId,
							      ID itemId) const;

template <>
QString RestRouter<FixtureGroupType>::getPath() const;

template <>
QHttpServerResponse RestRouter<FixtureGroupType>::get(const SessionShared& session,
						      const QHttpServerRequest& req) const;

template <>
QString RestRouter<FixtureGroupOwner>::getPath() const;

template <>
QHttpServerResponse RestRouter<FixtureGroupOwner>::get(const SessionShared& session,
						       const QHttpServerRequest& req) const;

} // namespace light

#endif // FIXTUREGROUPROUTER_H
