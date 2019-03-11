#ifndef POSTGRESCRUDCONTRAGENT_H
#define POSTGRESCRUDCONTRAGENT_H

#include "Contragent.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
ContragentSharedList PostgresCrud<Contragent>::sel<>() const;

template <>
ContragentSharedList PostgresCrud<Contragent>::sel(const IDList& ids) const;

template <>
ContragentShared PostgresCrud<Contragent>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDCONTRAGENT_H
