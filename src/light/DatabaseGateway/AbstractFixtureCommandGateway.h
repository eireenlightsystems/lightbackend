#ifndef ABSTRACTFIXTURECOMMANDGATEWAY_H
#define ABSTRACTFIXTURECOMMANDGATEWAY_H

#include "CommandStatus.h"
#include "typedefs.h"

#include <QDateTime>

namespace light {
struct FixtureCommandsFilter
{
  CommandStatus status;
  ID fixtureId;
  QDateTime from;
  QDateTime to;
};

class AbstractFixtureGateway
{
public:
  virtual ~AbstractFixtureGateway() = 0;
  virtual FixtureShared selectFixture(ID id) = 0;
  virtual FixtureSharedList selectFixtures(const QList<ID>& ids) = 0;
  virtual void saveFixture(const FixtureShared& fixture) = 0;
  virtual void saveFixtures(const FixtureSharedList& fixtures) = 0;
  virtual void deleteFixture(const FixtureShared& fixture) = 0;
  virtual void deleteFixtures(const FixtureSharedList& fixtures) = 0;
};

class AbstractFixtureCommandGateway
{
public:
  virtual ~AbstractFixtureCommandGateway() = 0;
  virtual FixtureCommandShared selectCommand(ID id) = 0;
  virtual FixtureCommandSharedList selectCommands(const QList<ID>& ids) = 0;
  virtual void deleteCommand(const FixtureCommandShared& command) = 0;
  virtual void deleteCommands(const FixtureCommandSharedList& commands) = 0;
};

class AbstractFixtureLightLevelCommandGateway
{
public:
  virtual ~AbstractFixtureLightLevelCommandGateway() = 0;
  virtual FixtureLightLevelCommandShared selectLightLevelCommand(ID id) = 0;
  virtual FixtureLightLevelCommandSharedList selectLightLevelCommands(const QList<ID>& ids) = 0;
  virtual FixtureLightLevelCommandSharedList selectLightLevelCommands(const QDateTime& dateTime) = 0;
  virtual FixtureLightLevelCommandSharedList selectLightLevelCommands(const FixtureCommandsFilter& filter) = 0;
  virtual void saveLightLevelCommand(const FixtureLightLevelCommandShared& command) = 0;
  virtual void saveLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) = 0;
  virtual void deleteLightLevelCommand(const FixtureLightLevelCommandShared& command) = 0;
  virtual void deleteLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) = 0;
};

class AbstractFixtureLightSpeedCommandGateway
{
public:
  virtual ~AbstractFixtureLightSpeedCommandGateway() = 0;
  virtual FixtureLightSpeedCommandShared selectLightSpeedCommand(ID id) = 0;
  virtual FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QList<ID>& ids) = 0;
  virtual FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QDateTime& dateTime) = 0;
  virtual FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const FixtureCommandsFilter& filter) = 0;
  virtual void saveLightSpeedCommand(const FixtureLightSpeedCommandShared& command) = 0;
  virtual void saveLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) = 0;
  virtual void deleteLightSpeedCommand(const FixtureLightSpeedCommandShared& command) = 0;
  virtual void deleteLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) = 0;
};

class AbstractDeviceCommandGateway
{
public:
  virtual ~AbstractDeviceCommandGateway() = 0;
  virtual AbstractDeviceCommandSharedList selectDeviceInCommandsInQueue(const QDateTime& dateTime) = 0;
  virtual void saveDeviceCommands(const AbstractDeviceCommandSharedList& deviceCommands) = 0;
  virtual QDateTime getClosestDeviceCommandDateTime() = 0;
};

class AbstractFixtureCommandFacadeGateway : public AbstractFixtureGateway,
					    public AbstractFixtureCommandGateway,
					    public AbstractFixtureLightLevelCommandGateway,
					    public AbstractFixtureLightSpeedCommandGateway,
					    public AbstractDeviceCommandGateway
{
};
} // namespace light

#endif // ABSTRACTFIXTURECOMMANDGATEWAY_H
