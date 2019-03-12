#ifndef POSTGRESCRUDSUBSTATION_H
#define POSTGRESCRUDSUBSTATION_H

#include "PostgresCrud.h"
#include "Substation.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
SubstationSharedList PostgresCrud<Substation>::sel<>() const;

template <>
SubstationSharedList PostgresCrud<Substation>::sel(const IDList& ids) const;

template <>
SubstationShared PostgresCrud<Substation>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDSUBSTATION_H
