#ifndef POSTGRESCRUDUSER_H
#define POSTGRESCRUDUSER_H

#include "PostgresCrud.h"
#include "User.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<User> : public Editor<User>
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

#endif // POSTGRESCRUDUSER_H
