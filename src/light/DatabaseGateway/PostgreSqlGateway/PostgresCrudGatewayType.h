#ifndef POSTGRESCRUDGATEWAYTYPE_H
#define POSTGRESCRUDGATEWAYTYPE_H

#include "GatewayType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<GatewayType> : public Reader<GatewayType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGATEWAYTYPE_H
