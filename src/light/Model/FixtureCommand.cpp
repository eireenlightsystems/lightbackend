#include "FixtureCommand.h"

namespace light {
FixtureCommand::~FixtureCommand() {
}

ID FixtureCommand::getCommandId() const {
  return commandId;
}

void FixtureCommand::setCommandId(const ID& value) {
  commandId = value;
}

ID FixtureCommand::getFixtureId() const {
  return fixtureId;
}

void FixtureCommand::setFixtureId(const ID& value) {
  fixtureId = value;
}

QDateTime FixtureCommand::getStartDateTime() const {
  return startDateTime;
}

void FixtureCommand::setStartDateTime(const QDateTime& value) {
  startDateTime = value;
}

CommandStatus FixtureCommand::getStatus() const {
  return status;
}

void FixtureCommand::setStatus(const CommandStatus& value) {
  status = value;
}

bool FixtureCommand::getDeletable() const {
  return status == CommandStatus::InQueue;
}

} // namespace light
