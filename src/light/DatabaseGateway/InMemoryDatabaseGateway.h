#ifndef INMEMORYDATABASEGATEWAY_H
#define INMEMORYDATABASEGATEWAY_H

#include "AbstractFixtureCommandGateway.h"

#include <QMap>

namespace light {
class InMemoryDatabaseGateway : public AbstractFixtureCommandFacadeGateway
{
public:
  static ID currentId;
  static ID generateId();
  InMemoryDatabaseGateway() = default;

  // AbstractDeviceCommandGateway interface
public:
  AbstractDeviceCommandSharedList selectDeviceInCommandsInQueue(const QDateTime &dateTime) override;
  void saveDeviceCommands(const AbstractDeviceCommandSharedList &deviceCommands) override;
  QDateTime getClosestDeviceCommandDateTime() override;

  // AbstractFixtureLightSpeedCommandGateway interface
public:
  FixtureLightSpeedCommandShared selectLightSpeedCommand(ID id) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QList<ID> &ids) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QDateTime &dateTime) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const FixtureCommandsFilter &filter) override;
  void saveLightSpeedCommand(const FixtureLightSpeedCommandShared &command) override;
  void saveLightSpeedCommands(const FixtureLightSpeedCommandSharedList &commands) override;
  void deleteLightSpeedCommand(const FixtureLightSpeedCommandShared &command) override;
  void deleteLightSpeedCommands(const FixtureLightSpeedCommandSharedList &commands) override;

  // AbstractFixtureLightLevelCommandGateway interface
public:
  FixtureLightLevelCommandShared selectLightLevelCommand(ID id) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const QList<ID> &ids) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const QDateTime &dateTime) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const FixtureCommandsFilter &filter) override;
  void saveLightLevelCommand(const FixtureLightLevelCommandShared &command) override;
  void saveLightLevelCommands(const FixtureLightLevelCommandSharedList &commands) override;
  void deleteLightLevelCommand(const FixtureLightLevelCommandShared &command) override;
  void deleteLightLevelCommands(const FixtureLightLevelCommandSharedList &commands) override;

  // AbstractFixtureCommandGateway interface
public:
  FixtureCommandShared selectCommand(ID id) override;
  FixtureCommandSharedList selectCommands(const QList<ID> &ids) override;
  void deleteCommand(const FixtureCommandShared &command) override;
  void deleteCommands(const FixtureCommandSharedList &commands) override;

  // AbstractFixtureGateway interface
public:
  FixtureShared selectFixture(ID id) override;
  FixtureSharedList selectFixtures(const QList<ID> &ids) override;
  void saveFixture(const FixtureShared &fixture) override;
  void saveFixtures(const FixtureSharedList &fixtures) override;
  void deleteFixture(const FixtureShared &fixture) override;
  void deleteFixtures(const FixtureSharedList &fixtures) override;

private:
  QMultiMap<QDateTime, AbstractDeviceCommandShared> allDeviceComands;
  QMultiMap<QDateTime, FixtureLightLevelCommandShared> allDatabaseComands;

  QHash<ID, FixtureShared> fixtures;
};
} // namespace light

#endif // INMEMORYDATABASEGATEWAY_H
