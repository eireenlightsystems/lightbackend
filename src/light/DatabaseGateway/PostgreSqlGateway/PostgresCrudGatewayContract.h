#ifndef POSTGRESCRUDGATEWAYCONTRACT_H
#define POSTGRESCRUDGATEWAYCONTRACT_H

#include "Gateway.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<GatewayContract> : public Reader<GatewayContract>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGATEWAYCONTRACT_H
