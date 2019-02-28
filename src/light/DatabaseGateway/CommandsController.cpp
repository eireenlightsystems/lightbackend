#include "CommandsController.h"

#include "AbstractFixtureCommandGateway.h"
#include "DeleteCommandException.h"
#include "Fixture.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "MissingFixtureGatewayLinkException.h"
#include "NotImplementedException.h"

#include <QDebug>

namespace light {
void CommandsController::setFixturesLightLevel(const FixtureLightLevelCommandSharedList& commands) {
  checkFixtureGatewayLink(commands);
  fixtureCommandGateway->saveLightLevelCommands(commands);
}

void CommandsController::setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList& commands) {
  checkFixtureGatewayLink(commands);
  fixtureCommandGateway->saveLightSpeedCommands(commands);
}

void CommandsController::deleteFixturesCommands(const QList<ID>& ids) {
  auto commands = fixtureCommandGateway->selectCommands(ids);
  checkCommandBeforeDelete(commands);
  fixtureCommandGateway->deleteCommands(commands);
}

void CommandsController::editFixturesCommands(const FixtureLightLevelCommandSharedList& commands) {
  Q_UNUSED(commands)
  qCritical() << Q_FUNC_INFO << "not implemented";
  throw NotImplementedException(Q_FUNC_INFO);
}

AbstractDeviceCommandSharedList CommandsController::getDeviceCommandsByDateTime(const QDateTime& dateTime) const {
  return fixtureCommandGateway->selectDeviceInCommandsInQueue(dateTime);
}

FixtureLightLevelCommandSharedList
CommandsController::getFixtureLightLevelCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const {
  return fixtureCommandGateway->selectLightLevelCommands(filter);
}

FixtureLightSpeedCommandSharedList
CommandsController::getFixtureLightSpeedCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const {
  return fixtureCommandGateway->selectLightSpeedCommands(filter);
}

template <typename ConcreteFixtureCommandList>
void CommandsController::checkFixtureGatewayLink(const ConcreteFixtureCommandList& commands) const {
  QList<ID> fixturesIds;
  std::transform(commands.cbegin(),
		 commands.cend(),
		 std::back_inserter(fixturesIds),
		 [](const typename ConcreteFixtureCommandList::value_type& c) { return c->getFixtureId(); });
  auto fixtures = fixtureCommandGateway->selectFixtures(fixturesIds);
  auto findedIt =
      std::find_if(fixtures.cbegin(), fixtures.cend(), [](const FixtureShared& f) { return !f->getHasGatewayLink(); });
  if (findedIt != fixtures.cend()) {
    throw MissingFixtureGatewayLinkException(findedIt->data()->getId());
  }
}

void CommandsController::checkCommandBeforeDelete(const FixtureCommandSharedList& commands) const {
  FixtureCommandSharedList notDeletableCommands;
  std::copy_if(commands.cbegin(),
	       commands.cend(),
	       std::back_inserter(notDeletableCommands),
	       [](const FixtureCommandShared& c) { return !c->getDeletable(); });
  if (notDeletableCommands.count()) {
    QList<ID> commandsIds;
    std::transform(notDeletableCommands.cbegin(),
		   notDeletableCommands.cend(),
		   std::back_inserter(commandsIds),
		   [](const FixtureCommandShared& c) { return c->getCommandId(); });
    throw DeleteCommandException(commandsIds);
  }
}

AbstractFixtureCommandFacadeGatewayShared CommandsController::getFixtureCommandGateway() const {
  return fixtureCommandGateway;
}

void CommandsController::setFixtureCommandGateway(const AbstractFixtureCommandFacadeGatewayShared& value) {
  fixtureCommandGateway = value;
}
} // namespace light
