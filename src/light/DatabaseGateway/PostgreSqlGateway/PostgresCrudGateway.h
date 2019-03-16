#ifndef POSTGRESCRUDGATEWAY_H
#define POSTGRESCRUDGATEWAY_H

#include "Gateway.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Gateway> : public Editor<Gateway>
{
public:
  PostgresCrud();

protected:
  Shared parse(const QSqlRecord& record) const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGATEWAY_H
