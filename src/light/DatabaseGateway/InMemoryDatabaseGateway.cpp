#include "InMemoryDatabaseGateway.h"

#include "AbstractFixtureCommandGateway.h"
#include "Fixture.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureSwitchOnDeviceCommand.h"

namespace light {

ID InMemoryDatabaseGateway::currentId = 0;

ID InMemoryDatabaseGateway::generateId() {
  return ++currentId;
}

/*
void InMemoryDatabaseGateway::editFixturesCommands(const FixtureLightLevelCommandSharedList& commands) {
  for (const auto& editCommand : commands) {
    {
      auto allDeviceComandsValues = allDeviceComands.values();
      auto it = std::find_if(allDeviceComandsValues.cbegin(),
			     allDeviceComandsValues.cend(),
			     [&editCommand](const AbstractDeviceCommandShared& deviceCommand) {
			       return deviceCommand->getCommandId() == editCommand->getCommandId();
			     });
      if (it != allDeviceComandsValues.cend()) {
	AbstractDeviceCommandShared currentCommand = *it;
	if (auto fixtureSwitchOnCommand = currentCommand.dynamicCast<FixtureSwitchOnDeviceCommand>()) {
	  allDeviceComands.remove(currentCommand->getDateTime(), currentCommand);
	  fixtureSwitchOnCommand->setWorkLevel(editCommand->getWorkLevel());
	  fixtureSwitchOnCommand->setStandbyLevel(editCommand->getStandbyLevel());
	  fixtureSwitchOnCommand->setDateTime(editCommand->getStartDateTime());
	  allDeviceComands.insertMulti(fixtureSwitchOnCommand->getDateTime(), fixtureSwitchOnCommand);
	}
      }
    }

    {
      auto allComandsValues = allDatabaseComands.values();
      auto it = std::find_if(allComandsValues.begin(),
			     allComandsValues.end(),
			     [&editCommand](const FixtureLightLevelCommandShared& deviceCommand) {
			       return deviceCommand->getCommandId() == editCommand->getCommandId();
			     });
      if (it != allComandsValues.end()) {
	FixtureLightLevelCommandShared currentCommand = *it;
	allDatabaseComands.remove(currentCommand->getStartDateTime(), currentCommand);
	FixtureLightLevelCommandShared newCommand = currentCommand;
	newCommand->setWorkLevel(editCommand->getWorkLevel());
	newCommand->setStandbyLevel(editCommand->getStandbyLevel());
	newCommand->setStartDateTime(editCommand->getStartDateTime());
	allDatabaseComands.insertMulti(newCommand->getStartDateTime(), newCommand);
      }
    }
  }
}
*/

AbstractDeviceCommandSharedList InMemoryDatabaseGateway::selectDeviceInCommandsInQueue(const QDateTime& dateTime) {
  return allDeviceComands.values(dateTime);
}

void InMemoryDatabaseGateway::saveDeviceCommands(const AbstractDeviceCommandSharedList& deviceCommands){
    Q_UNUSED(deviceCommands)}

QDateTime InMemoryDatabaseGateway::getClosestDeviceCommandDateTime() {
  const QList<QDateTime> timestamps = allDeviceComands.uniqueKeys();
  auto it = std::min_element(timestamps.cbegin(), timestamps.cend());
  if (it != timestamps.cend())
    return *it;

  return QDateTime();
}

FixtureLightSpeedCommandShared InMemoryDatabaseGateway::selectLightSpeedCommand(ID id) {
  Q_UNUSED(id)
  return FixtureLightSpeedCommandShared();
}

FixtureLightSpeedCommandSharedList InMemoryDatabaseGateway::selectLightSpeedCommands(const QList<ID>& ids) {
  Q_UNUSED(ids)
  return FixtureLightSpeedCommandSharedList();
}

FixtureLightSpeedCommandSharedList InMemoryDatabaseGateway::selectLightSpeedCommands(const QDateTime& dateTime) {
  Q_UNUSED(dateTime)
  return FixtureLightSpeedCommandSharedList();
}

FixtureLightSpeedCommandSharedList
InMemoryDatabaseGateway::selectLightSpeedCommands(const FixtureCommandsFilter& filter) {
  Q_UNUSED(filter)

  return FixtureLightSpeedCommandSharedList();
}

void InMemoryDatabaseGateway::saveLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  Q_UNUSED(command)
}

void InMemoryDatabaseGateway::saveLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) {
  Q_UNUSED(commands)
}

void InMemoryDatabaseGateway::deleteLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  Q_UNUSED(command)
}

void InMemoryDatabaseGateway::deleteLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands){
    Q_UNUSED(commands)}

FixtureLightLevelCommandShared InMemoryDatabaseGateway::selectLightLevelCommand(ID id) {
  Q_UNUSED(id)
  return FixtureLightLevelCommandShared();
}

FixtureLightLevelCommandSharedList InMemoryDatabaseGateway::selectLightLevelCommands(const QList<ID>& ids) {
  Q_UNUSED(ids)
  return FixtureLightLevelCommandSharedList();
}

FixtureLightLevelCommandSharedList InMemoryDatabaseGateway::selectLightLevelCommands(const QDateTime& dateTime) {
  Q_UNUSED(dateTime)
  return FixtureLightLevelCommandSharedList();
}

FixtureLightLevelCommandSharedList
InMemoryDatabaseGateway::selectLightLevelCommands(const FixtureCommandsFilter& filter) {
  FixtureLightLevelCommandSharedList result;
  for (const auto& key : allDatabaseComands.uniqueKeys()) {
    if (filter.from <= key and key <= filter.to) {
      auto values = allDatabaseComands.values(key);
      std::copy_if(values.cbegin(),
		   values.cend(),
		   std::back_inserter(result),
		   [filter](const FixtureLightLevelCommandShared& command) {
		     return command->getFixtureId() == filter.fixtureId;
		   });
    }
  }
  return result;
}

void InMemoryDatabaseGateway::saveLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  Q_UNUSED(command)
}

void InMemoryDatabaseGateway::saveLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) {
  for (auto command : commands) {
    command->setId(generateId());
    auto switchOnCommand = FixtureSwitchOnDeviceCommandShared::create(1, 1, 1, 1);
    switchOnCommand->setDateTime(command->getStartDateTime());
    switchOnCommand->setCommandId(command->getId());
    switchOnCommand->setWorkLevel(command->getWorkLevel());
    switchOnCommand->setStandbyLevel(command->getStandbyLevel());
    allDeviceComands.insertMulti(command->getStartDateTime(), switchOnCommand);
    allDatabaseComands.insertMulti(command->getStartDateTime(), command);
  }
}

void InMemoryDatabaseGateway::deleteLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  Q_UNUSED(command)
}

void InMemoryDatabaseGateway::deleteLightLevelCommands(const FixtureLightLevelCommandSharedList& commands){
    Q_UNUSED(commands)}

FixtureCommandShared InMemoryDatabaseGateway::selectCommand(ID id) {
  Q_UNUSED(id)
  return FixtureCommandShared();
}

FixtureCommandSharedList InMemoryDatabaseGateway::selectCommands(const QList<ID>& ids) {
  Q_UNUSED(ids)
  return FixtureCommandSharedList();
}

void InMemoryDatabaseGateway::deleteCommand(const FixtureCommandShared& command) {
  Q_UNUSED(command)
}

void InMemoryDatabaseGateway::deleteCommands(const FixtureCommandSharedList& fixtureCommands) {
  QList<ID> ids;
  std::transform(fixtureCommands.begin(),
		 fixtureCommands.end(),
		 std::back_inserter(ids),
		 [](const FixtureCommandSharedList::value_type& c) { return c->getId(); });

  for (auto commandId : ids) {
    QMutableMapIterator<QDateTime, AbstractDeviceCommandShared> allDeviceComandsIterator(allDeviceComands);
    while (allDeviceComandsIterator.hasNext()) {
      allDeviceComandsIterator.next();
      auto currentDeviceCommand = allDeviceComandsIterator.value();
      if (currentDeviceCommand->getCommandId() == commandId) {
	allDeviceComandsIterator.remove();
      }
    }
    QMutableMapIterator<QDateTime, FixtureLightLevelCommandShared> allComandsIterator(allDatabaseComands);
    while (allComandsIterator.hasNext()) {
      allComandsIterator.next();
      auto& currentCommand = allComandsIterator.value();
      if (currentCommand->getId() == commandId) {
	allComandsIterator.remove();
      }
    }
  }
}

FixtureShared InMemoryDatabaseGateway::selectFixture(ID id) {
  return fixtures.value(id);
}

FixtureSharedList InMemoryDatabaseGateway::selectFixtures(const QList<ID>& ids) {
  FixtureSharedList result;
  for (auto id : ids) {
    result << selectFixture(id);
  }
  return result;
}

void InMemoryDatabaseGateway::saveFixture(const FixtureShared& fixture) {
  fixtures[fixture->getId()] = fixture;
}

void InMemoryDatabaseGateway::saveFixtures(const FixtureSharedList& fixtures) {
  for (auto fixture : fixtures) {
    saveFixture(fixture);
  }
}

void InMemoryDatabaseGateway::deleteFixture(const FixtureShared& fixture) {
  Q_UNUSED(fixture)
}

void InMemoryDatabaseGateway::deleteFixtures(const FixtureSharedList& fixtures) {
  Q_UNUSED(fixtures)
}

} // namespace light
