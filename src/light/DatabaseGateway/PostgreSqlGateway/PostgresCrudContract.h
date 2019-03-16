#ifndef POSTGRESCRUDCONTRACT_H
#define POSTGRESCRUDCONTRACT_H

#include "Contract.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Contract> : public Reader<Contract>
{
public:
  PostgresCrud();

protected:
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDCONTRACT_H
