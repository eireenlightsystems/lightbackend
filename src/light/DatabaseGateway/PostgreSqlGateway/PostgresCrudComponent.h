#ifndef POSTGRESCRUDCOMPONENT_H
#define POSTGRESCRUDCOMPONENT_H


#include "Component.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Component> : public Editor<Component>
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
