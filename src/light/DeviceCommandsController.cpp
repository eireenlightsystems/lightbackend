#include "DeviceCommandsController.h"

#include "CommandsController.h"

#include <QDateTime>

namespace light {
DeviceCommandsController::DeviceCommandsController(QObject* parent) : QObject(parent) {
}

void DeviceCommandsController::setCommandController(const CommandsControllerShared& value) {
  this->commandController = value;
}

void DeviceCommandsController::setFixturesLightLevel(const FixtureLightLevelCommandSharedList& commands) {
  commandController->setFixturesLightLevel(commands);
}

void DeviceCommandsController::setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList& commands) {
  commandController->setFixturesLightSpeed(commands);
}

void DeviceCommandsController::deleteFixturesCommands(const QList<ID>& commands) {
  commandController->deleteFixturesCommands(commands);
}

} // namespace light
