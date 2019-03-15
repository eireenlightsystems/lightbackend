#ifndef POSTGRESCRUDFIXTUREGROUP_H
#define POSTGRESCRUDFIXTUREGROUP_H

#include "FixtureGroup.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel<ID, ID>(ID ownerId, ID typeId) const;

template <>
template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel<QVariantHash>(const QVariantHash filters) const;

template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel(const IDList& ids) const;

template <>
void PostgresCrud<FixtureGroup>::ins(const FixtureGroupShared& fixtureGroup) const;

template <>
void PostgresCrud<FixtureGroup>::upd(const FixtureGroupShared& fixtureGroup) const;

template <>
void PostgresCrud<FixtureGroup>::del(const FixtureGroupSharedList& fixtureGroups) const;

template <>
FixtureGroupShared PostgresCrud<FixtureGroup>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREGROUP_H
