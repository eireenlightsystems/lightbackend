#ifndef POSTGRESCRUDCONTRACT_H
#define POSTGRESCRUDCONTRACT_H

#include "Contract.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
ContractSharedList PostgresCrud<Contract>::sel(const IDList& ids) const;

template <>
ContractShared PostgresCrud<Contract>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDCONTRACT_H
