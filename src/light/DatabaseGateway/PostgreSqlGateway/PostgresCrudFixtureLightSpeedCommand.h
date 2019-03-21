#ifndef POSTGRESCRUDLIGHTSPEEDCOMMAND_H
#define POSTGRESCRUDLIGHTSPEEDCOMMAND_H


#include "FixtureLightSpeedCommand.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureLightSpeedCommand> : public Editor<FixtureLightSpeedCommand>
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

#endif // POSTGRESCRUDLIGHTSPEEDCOMMAND_H
