#ifndef POSTGRESCRUDFIXTURETYPE_H
#define POSTGRESCRUDFIXTURETYPE_H

#include "FixtureType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureTypeSharedList PostgresCrud<FixtureType>::sel<>() const;

template <>
FixtureTypeSharedList PostgresCrud<FixtureType>::sel(const IDList& ids) const;

template <>
FixtureTypeShared PostgresCrud<FixtureType>::parse(const QSqlRecord& record) const;

}
}

#endif // POSTGRESCRUDFIXTURETYPE_H
