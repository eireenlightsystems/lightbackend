#ifndef POSTGRESCRUDFIXTUREGROUPTYPE_H
#define POSTGRESCRUDFIXTUREGROUPTYPE_H

#include "FixtureGroupType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureGroupTypeSharedList PostgresCrud<FixtureGroupType>::sel<>() const;

template <>
template <>
FixtureGroupTypeSharedList PostgresCrud<FixtureGroupType>::sel<QVariantHash>(const QVariantHash filters) const;

template <>
FixtureGroupTypeSharedList PostgresCrud<FixtureGroupType>::sel(const IDList& ids) const;

template <>
FixtureGroupTypeShared PostgresCrud<FixtureGroupType>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREGROUPTYPE_H
