#ifndef SPEEDTOLIGHTBASEDEVICECOMMANDPOSTGRESCRUD_H
#define SPEEDTOLIGHTBASEDEVICECOMMANDPOSTGRESCRUD_H

#include "SpeedToLightBaseDeviceCommand.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>
  : public Editor<CommandsScheduler::SpeedToLightBaseDeviceCommand>
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

#endif // SPEEDTOLIGHTBASEDEVICECOMMANDPOSTGRESCRUD_H
