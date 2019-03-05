#ifndef POSTGRESCRUDGEOGRAPH_H
#define POSTGRESCRUDGEOGRAPH_H

#include "Geograph.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
GeographSharedList PostgresCrud<Geograph>::sel(const IDList& ids) const;

template <>
GeographShared PostgresCrud<Geograph>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGEOGRAPH_H
