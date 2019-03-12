#ifndef POSTGRESCRUDFIXTURE_H
#define POSTGRESCRUDFIXTURE_H

#include "Fixture.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureSharedList PostgresCrud<Fixture>::sel<ID, ID, ID, ID, ID, ID, ID>(ID geographId, ID ownerId, ID fixtureTypeId, ID substationId, ID modeId, ID contractId, ID nodeId) const;

template <>
FixtureSharedList PostgresCrud<Fixture>::sel(const IDList& ids) const;

template <>
void PostgresCrud<Fixture>::ins(const FixtureShared& fixture) const;

template <>
void PostgresCrud<Fixture>::upd(const FixtureShared& fixture) const;

template <>
void PostgresCrud<Fixture>::del(const FixtureSharedList& fixtures) const;

template <>
FixtureShared PostgresCrud<Fixture>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light
#endif // POSTGRESCRUDFIXTURE_H
