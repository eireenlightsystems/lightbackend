#ifndef POSTGRESCRUDFIXTUREHEIGHTTYPE_H
#define POSTGRESCRUDFIXTUREHEIGHTTYPE_H

#include "FixtureHeightType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureHeightTypeSharedList PostgresCrud<FixtureHeightType>::sel<>() const;

template <>
template <>
FixtureHeightTypeSharedList PostgresCrud<FixtureHeightType>::sel<QVariantHash>(const QVariantHash filters) const;

template <>
FixtureHeightTypeSharedList PostgresCrud<FixtureHeightType>::sel(const IDList& ids) const;

template <>
FixtureHeightTypeShared PostgresCrud<FixtureHeightType>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREHEIGHTTYPE_H
