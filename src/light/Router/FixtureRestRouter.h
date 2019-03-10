#ifndef FIXTURERESTROUTER_H
#define FIXTURERESTROUTER_H

#include "RestRouter.h"
#include "FixtureType.h"
#include "FixtureHeightType.h"
#include "Substation.h"

namespace light {

template <>
QString RestRouter<FixtureType>::getPath() const;

template<>
QList<QHttpServerRequest::Method> RestRouter<FixtureType>::getAccessibleMethods() const;

template <>
QHttpServerResponse RestRouter<FixtureType>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QString RestRouter<FixtureHeightType>::getPath() const;

template<>
QList<QHttpServerRequest::Method> RestRouter<FixtureHeightType>::getAccessibleMethods() const;

template <>
QHttpServerResponse RestRouter<FixtureHeightType>::get(const SessionShared& session, const QHttpServerRequest& req) const;

template <>
QString RestRouter<Substation>::getPath() const;

template<>
QList<QHttpServerRequest::Method> RestRouter<Substation>::getAccessibleMethods() const;

template <>
QHttpServerResponse RestRouter<Substation>::get(const SessionShared& session, const QHttpServerRequest& req) const;

} // namespace light

#endif // FIXTURERESTROUTER_H
