#ifndef POSTGRESCRUDROLE_H
#define POSTGRESCRUDROLE_H


#include "Role.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Role> : public Editor<Role>
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

#endif // POSTGRESCRUDROLE_H
