#include "DeviceCommandsController.h"

#include "CommandsScheduler.h"
#include "MqttDeviceCommandPublisher.h"
#include "CommandsController.h"
#include "SchedulerGateway.h"

namespace light {
DeviceCommandsController::DeviceCommandsController(QObject* parent)
  : QObject(parent)
  , commandsScheduler(CommandsSchedulerShared::create())
  , deviceCommandPublisher(MqttDeviceCommandPublisherShared::create()) {
  connect(commandsScheduler.data(), &CommandsScheduler::timeout, this, &DeviceCommandsController::onSchedulerTimeout);
}

void DeviceCommandsController::setMqttClient(const QMqttClientShared& mqttClient) {
  deviceCommandPublisher->setMqttClient(mqttClient);
}

void DeviceCommandsController::setCommandController(const CommandsControllerShared &value) {
  this->commandController = value;
}

void DeviceCommandsController::onSchedulerTimeout(const QDateTime& datetime) {
  auto commands = commandController->getDeviceCommandsByDateTime(datetime);
  deviceCommandPublisher->publish(commands);
  schedulerGateway->markAsSentCommandsByDateTime(datetime);
  commandsScheduler->checkUpdates();
}

SchedulerGatewayShared DeviceCommandsController::getSchedulerGateway() const {
  return schedulerGateway;
}

void DeviceCommandsController::setSchedulerGateway(const SchedulerGatewayShared& value) {
  commandsScheduler->setSchedulerGateway(value);
  commandsScheduler->checkUpdates();
  schedulerGateway = value;
}

MqttDeviceCommandPublisherShared DeviceCommandsController::getDeviceCommandPublisher() const {
  return deviceCommandPublisher;
}

void DeviceCommandsController::setFixturesLightLevel(const FixtureLightLevelCommandSharedList& commands) {
  commandController->setFixturesLightLevel(commands);
  commandsScheduler->checkUpdates();
}

void DeviceCommandsController::setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList& commands) {
  commandController->setFixturesLightSpeed(commands);
  commandsScheduler->checkUpdates();
}

void DeviceCommandsController::deleteFixturesCommands(const QList<ID>& commands) {
  commandController->deleteFixturesCommands(commands);
  commandsScheduler->checkUpdates();
}

CommandsSchedulerShared DeviceCommandsController::getCommandsWatchDog() const {
  return commandsScheduler;
}

QDateTime DeviceCommandsController::getCheckCommandDateTime() const {
  return commandsScheduler->getCheckCommandDateTime();
}
} // namespace light
