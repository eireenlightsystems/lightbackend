#ifndef POSTGRESCRUDGEOGRAPH_H
#define POSTGRESCRUDGEOGRAPH_H


#include "PostgresCrud.h"
#include "Geograph.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
GeographSharedList PostgresCrud<Geograph>::sel<const IDList&>(const IDList& ids) const;

template <>
GeographShared PostgresCrud<Geograph>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGEOGRAPH_H
