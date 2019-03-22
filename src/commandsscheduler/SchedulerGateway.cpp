#include "SchedulerGateway.h"

#include "CommandsSchedulerTypeDefs.h"
#include "Fixture.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"

#include <QDebug>

using FixtureSharedList = light::FixtureSharedList;
using FixtureShared = light::FixtureShared;

namespace light {
namespace CommandsScheduler {
QDateTime SchedulerGateway::getClosestCommandDateTime() const {
  return gateways.deviceCommandGateway->getClosestDeviceCommandDateTime();
}

void SchedulerGateway::markAsSentCommandsByDateTime(const QDateTime& dateTime) {
  markAsSentLightLevel(dateTime);
  markAsSentLightSpeed(dateTime);
}

void SchedulerGateway::markAsSentLightLevel(const QDateTime& dateTime) {
  FixtureSharedList fixtures;
  auto lightLevelCommands = gateways.lightLevelCommandGateway->selectLightLevelCommands(dateTime);
  for (auto command : lightLevelCommands) {
    auto fixture = gateways.fixtureGateway->selectFixture(command->getFixtureId());
    fixture->setStandbyLevel(command->getStandbyLevel());
    fixture->setWorkLevel(command->getWorkLevel());
    command->setStatus(light::CommandStatus::Done);

    fixtures << fixture;
  }
  gateways.lightLevelCommandGateway->saveLightLevelCommands(lightLevelCommands);
  gateways.fixtureGateway->saveFixtures(fixtures);
}

void SchedulerGateway::markAsSentLightSpeed(const QDateTime& dateTime) {
  QHash<ID, FixtureShared> fixtures;
  auto lightSpeedCommands = gateways.lightSpeedCommandGateway->selectLightSpeedCommands(dateTime);
  for (auto command : lightSpeedCommands) {
    FixtureShared fixture;
    if (fixtures.contains(command->getFixtureId())) {
      fixture = fixtures.value(command->getFixtureId());
    } else {
      fixture = gateways.fixtureGateway->selectFixture(command->getFixtureId());
    }
    switch (command->getDirectionType()) {
      case light::FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::None: break;
      case light::FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork:
	fixture->setSpeedUp(command->getSpeed());
	break;
      case light::FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::WorkToStandby:
	fixture->setSpeedDown(command->getSpeed());
	break;
    }
    command->setStatus(light::CommandStatus::Done);

    fixtures[fixture->getId()] = fixture;
  }
  gateways.lightSpeedCommandGateway->saveLightSpeedCommands(lightSpeedCommands);
  gateways.fixtureGateway->saveFixtures(fixtures.values());
}
} // namespace CommandsScheduler

} // namespace light
