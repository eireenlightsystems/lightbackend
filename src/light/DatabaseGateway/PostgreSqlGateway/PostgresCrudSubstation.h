#ifndef POSTGRESCRUDSUBSTATION_H
#define POSTGRESCRUDSUBSTATION_H

#include "PostgresCrud.h"
#include "Substation.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Substation> : public Editor<Substation>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDSUBSTATION_H
