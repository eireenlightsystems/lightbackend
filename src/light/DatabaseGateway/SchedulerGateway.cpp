#include "SchedulerGateway.h"

#include "AbstractFixtureCommandGateway.h"
#include "Fixture.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"

#include <QDebug>

namespace light {
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
    command->setStatus(CommandStatus::Done);

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
      case FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::None: break;
      case FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork:
	fixture->setSpeedUp(command->getSpeed());
	break;
      case FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::WorkToStandby:
	fixture->setSpeedDown(command->getSpeed());
	break;
    }
    command->setStatus(CommandStatus::Done);

    fixtures[fixture->getId()] = fixture;
  }
  gateways.lightSpeedCommandGateway->saveLightSpeedCommands(lightSpeedCommands);
  gateways.fixtureGateway->saveFixtures(fixtures.values());
}

SchedulerGateway::Gateways SchedulerGateway::getGateways() const {
  return gateways;
}

void SchedulerGateway::setGateways(const Gateways& value) {
  gateways = value;
}
} // namespace light
