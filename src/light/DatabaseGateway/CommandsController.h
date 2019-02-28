#ifndef POSTGRESGATEWAY_H
#define POSTGRESGATEWAY_H

#include "typedefs.h"

namespace light {
struct FixtureCommandsFilter;

class CommandsController
{
public:
  ~CommandsController() = default;

  void setFixturesLightLevel(const FixtureLightLevelCommandSharedList& commands);
  void setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList& commands);
  void deleteFixturesCommands(const QList<ID>& ids);
  void editFixturesCommands(const FixtureLightLevelCommandSharedList& commands);
  AbstractDeviceCommandSharedList getDeviceCommandsByDateTime(const QDateTime& dateTime) const;
  FixtureLightLevelCommandSharedList
  getFixtureLightLevelCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const;
  FixtureLightSpeedCommandSharedList
  getFixtureLightSpeedCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const;

  AbstractFixtureCommandFacadeGatewayShared getFixtureCommandGateway() const;
  void setFixtureCommandGateway(const AbstractFixtureCommandFacadeGatewayShared& value);

private:
  template <typename ConcreteFixtureCommandList>
  void checkFixtureGatewayLink(const ConcreteFixtureCommandList& commands) const;
  void checkCommandBeforeDelete(const FixtureCommandSharedList& commands) const;

private:
  AbstractFixtureCommandFacadeGatewayShared fixtureCommandGateway;
};
} // namespace light

#endif // POSTGRESGATEWAY_H
