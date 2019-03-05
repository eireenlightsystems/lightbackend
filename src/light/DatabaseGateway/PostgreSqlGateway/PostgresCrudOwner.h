#ifndef POSTGRESCRUDOWNER_H
#define POSTGRESCRUDOWNER_H

#include "Contragent.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
ContragentSharedList PostgresCrud<Contragent>::sel(const IDList& ids) const;

template <>
ContragentShared PostgresCrud<Contragent>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDOWNER_H
