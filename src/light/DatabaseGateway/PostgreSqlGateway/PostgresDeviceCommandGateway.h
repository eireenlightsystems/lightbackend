#ifndef POSTGRESDEVICECOMMANDGATEWAY_H
#define POSTGRESDEVICECOMMANDGATEWAY_H

#include "AbstractFixtureCommandGateway.h"
#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
class PostgresDeviceCommandGateway : public SqlDatabaseOwner, public AbstractDeviceCommandGateway
{
public:
  PostgresDeviceCommandGateway() = default;
  AbstractDeviceCommandSharedList selectDeviceInCommandsInQueue(const QDateTime& dateTime) override;
  void saveDeviceCommands(const AbstractDeviceCommandSharedList& deviceCommands) override;
  QDateTime getClosestDeviceCommandDateTime() override;

private:
  AbstractDeviceCommandSharedList getDeviceLightLevelCommandsByDateTime(const QDateTime& dateTime) const;
  AbstractDeviceCommandSharedList getDeviceLightSpeedCommandsByDateTime(const QDateTime& dateTime) const;

  FixtureSwitchOnDeviceCommandSharedList selectSwitchOnBase(const QString& sql, const BindParamsType& params) const;
  SpeedToLightBaseDeviceCommandSharedList selectSpeednBase(const QString& sql, const BindParamsType& params) const;
  FixtureSwitchOnDeviceCommandShared parseSwitchOnCommand(const QSqlRecord& record) const;
  SpeedToLightBaseDeviceCommandShared parseSpeedCommand(const QSqlRecord& record) const;
};
} // namespace PostgresqlGateway
} // namespace light
#endif // POSTGRESDEVICECOMMANDGATEWAY_H
