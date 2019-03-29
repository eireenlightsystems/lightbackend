#include "FixtureCommand.h"

namespace light {
FixtureCommand::~FixtureCommand() {
}

ID FixtureCommand::getId() const {
  return id;
}

void FixtureCommand::setId(const ID& value) {
  id = value;
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

ID FixtureCommandType::getId() const {
  return id;
}

void FixtureCommandType::setId(const ID& value) {
  id = value;
}

QString FixtureCommandType::getName() const {
  return name;
}

void FixtureCommandType::setName(const QString& value) {
  name = value;
}

ID FixtureCommandStatus::getId() const {
  return id;
}

void FixtureCommandStatus::setId(const ID& value) {
  id = value;
}

QString FixtureCommandStatus::getCode() const {
  return code;
}

void FixtureCommandStatus::setCode(const QString& value) {
  code = value;
}

QString FixtureCommandStatus::getName() const {
  return name;
}

void FixtureCommandStatus::setName(const QString& value) {
  name = value;
}

} // namespace light
