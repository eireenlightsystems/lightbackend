#ifndef POSTGRESCRUDCONTRACT_H
#define POSTGRESCRUDCONTRACT_H

#include "PostgresCrud.h"
#include "Contract.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
ContractSharedList PostgresCrud<Contract>::sel<const IDList&>(const IDList& ids) const;

template <>
ContractShared PostgresCrud<Contract>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDCONTRACT_H
