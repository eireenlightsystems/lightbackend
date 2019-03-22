#ifndef POSTGRESCRUDFIXTURELIGHTLEVELCOMMAND_H
#define POSTGRESCRUDFIXTURELIGHTLEVELCOMMAND_H

#include "FixtureLightLevelCommand.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureLightLevelCommand> : public Editor<FixtureLightLevelCommand>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& command) const override;
  BindParamsType getUpdateParams(const Shared& command) const override;
};

} // namespace PostgresqlGateway
} // namespace light
#endif // POSTGRESCRUDFIXTURELIGHTLEVELCOMMAND_H
