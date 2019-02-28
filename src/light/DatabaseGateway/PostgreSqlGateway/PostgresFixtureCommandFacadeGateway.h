#ifndef POSTGRESFIXTURECOMMANDFACADEGATEWAY_H
#define POSTGRESFIXTURECOMMANDFACADEGATEWAY_H

#include "AbstractFixtureCommandGateway.h"
#include "PostgresConnectionInfo.h"
#include "PostgresDeviceCommandGateway.h"
#include "PostgresFixtureCommandGateway.h"
#include "PostgresFixtureGateway.h"
#include "PostgresFixtureLightLevelCommandGateway.h"
#include "PostgresFixtureLightSpeedCommandGateway.h"

namespace light {
namespace PostgresqlGateway {
class PostgresFixtureCommandFacadeGateway : public AbstractFixtureCommandFacadeGateway
{
public:
  PostgresFixtureCommandFacadeGateway() = default;

  // AbstractDeviceCommandGateway interface
  AbstractDeviceCommandSharedList selectDeviceInCommandsInQueue(const QDateTime& dateTime) override;
  void saveDeviceCommands(const AbstractDeviceCommandSharedList& deviceCommands) override;
  QDateTime getClosestDeviceCommandDateTime() override;

  // AbstractFixtureLightSpeedCommandGateway interface
  FixtureLightSpeedCommandShared selectLightSpeedCommand(ID id) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QList<ID>& ids) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QDateTime& dateTime) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const FixtureCommandsFilter& filter) override;
  void saveLightSpeedCommand(const FixtureLightSpeedCommandShared& command) override;
  void saveLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) override;
  void deleteLightSpeedCommand(const FixtureLightSpeedCommandShared& command) override;
  void deleteLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) override;

  // AbstractFixtureLightLevelCommandGateway interface
  FixtureLightLevelCommandShared selectLightLevelCommand(ID id) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const QList<ID>& ids) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const QDateTime& dateTime) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const FixtureCommandsFilter& filter) override;
  void saveLightLevelCommand(const FixtureLightLevelCommandShared& command) override;
  void saveLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) override;
  void deleteLightLevelCommand(const FixtureLightLevelCommandShared& command) override;
  void deleteLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) override;

  // AbstractFixtureCommandGateway interface
  FixtureCommandShared selectCommand(ID id) override;
  FixtureCommandSharedList selectCommands(const QList<ID>& ids) override;
  void deleteCommand(const FixtureCommandShared& command) override;
  void deleteCommands(const FixtureCommandSharedList& commands) override;

  // AbstractFixtureGateway interface
  FixtureShared selectFixture(ID id) override;
  FixtureSharedList selectFixtures(const QList<ID>& ids) override;
  void saveFixture(const FixtureShared& fixture) override;
  void saveFixtures(const FixtureSharedList& fixtures) override;
  void deleteFixture(const FixtureShared& command) override;
  void deleteFixtures(const FixtureSharedList& commands) override;

  bool open(const PostgresConnectionInfo& connectionInfo);

protected:
  void setDb();

private:
  QSqlDatabase db;
  PostgresDeviceCommandGateway deviceCommandGateway;
  PostgresFixtureLightSpeedCommandGateway fixtureLightSpeedCommandGateway;
  PostgresFixtureLightLevelCommandGateway fixtureLightLevelCommandGateway;
  PostgresFixtureCommandGateway fixtureCommandGateway;
  PostgresFixtureGateway fixtureGateway;
};
} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESFIXTURECOMMANDFACADEGATEWAY_H
