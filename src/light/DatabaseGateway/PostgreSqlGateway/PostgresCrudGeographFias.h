#ifndef POSTGRESCRUDGEOGRAPHFIAS_H
#define POSTGRESCRUDGEOGRAPHFIAS_H

#include "GeographFias.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<GeographFias> : public Editor<GeographFias>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
protected:

  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGEOGRAPHFIAS_H
