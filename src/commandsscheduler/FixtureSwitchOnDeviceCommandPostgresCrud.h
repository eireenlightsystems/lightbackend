#ifndef FIXTURESWITCHONDEVICECOMMANDPOSTGRESCRUD_H
#define FIXTURESWITCHONDEVICECOMMANDPOSTGRESCRUD_H

#include "FixtureSwitchOnDeviceCommand.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>
  : public Editor<CommandsScheduler::FixtureSwitchOnDeviceCommand>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  QString getSelectSql() const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light
#endif // FIXTURESWITCHONDEVICECOMMANDPOSTGRESCRUD_H
