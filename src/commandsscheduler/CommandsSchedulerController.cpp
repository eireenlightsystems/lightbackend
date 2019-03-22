#include "CommandsSchedulerController.h"

#include "FixtureSwitchOnDeviceCommandPostgresCrud.h"
#include "MqttDeviceCommandPublisher.h"
#include "SchedulerFixture.h"
#include "SchedulerFixturePostgresCrud.h"
#include "SpeedToLightBaseDeviceCommandPostgresCrud.h"

#include <QDateTime>
#include <QMqttClient>

namespace light {
namespace CommandsScheduler {

CommandsSchedulerController::CommandsSchedulerController(QObject* parent) : QObject(parent) {
  connect(&timer, &QTimer::timeout, this, &CommandsSchedulerController::onSchedulerTimeout);
}

void CommandsSchedulerController::onSchedulerTimeout() {
  const auto currentDateTime = QDateTime::currentDateTime();
  publishSwitchOnCommand(currentDateTime);
  publishSpeedCommand(currentDateTime);
}

void CommandsSchedulerController::onMqttConnected() {
  onSchedulerTimeout();
  timer.start();
}

void CommandsSchedulerController::onMqttDisconnected() {
  timer.stop();
}

void CommandsSchedulerController::publishSwitchOnCommand(const QDateTime& datetime) {
  PostgresqlGateway::PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand> crud;
  crud.setSession(session);
  PostgresqlGateway::PostgresCrud<CommandsScheduler::SchedulerFixture> fixtureCrud;
  fixtureCrud.setSession(session);
  const QVariantHash params{
      {"dateTime", datetime},
  };
  auto lightLevelCommands = crud.sel(params);
  if (lightLevelCommands.count()) {
    for (auto c : lightLevelCommands) {
      if (deviceCommandPublisher->publish({c})) {
	auto fixture = c->getFixture();
	fixture->setWorkLevel(c->getWorkLevel());
	fixture->setStandbyLevel(c->getStandbyLevel());
	c->setStatus(CommandStatus::Done);
	crud.save(c);
	fixtureCrud.save(c->getFixture());
      }
    }
  }
}

void CommandsSchedulerController::publishSpeedCommand(const QDateTime& datetime) {
  PostgresqlGateway::PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand> commandCrud;
  commandCrud.setSession(session);
  PostgresqlGateway::PostgresCrud<CommandsScheduler::SchedulerFixture> fixtureCrud;
  fixtureCrud.setSession(session);
  const QVariantHash params{
      {"dateTime", datetime},
  };
  auto speedCommands = commandCrud.sel(params);
  if (speedCommands.count()) {
    for (auto c : speedCommands) {
      if (deviceCommandPublisher->publish({c})) {
	auto fixture = c->getFixture();
	if (c->getCommandNumber() == CommandNumber::SpeedToLightUp) {
	  fixture->setSpeedUp(c->getSpeed());
	} else if (c->getCommandNumber() == CommandNumber::SpeedToLightDown) {
	  fixture->setSpeedDown(c->getSpeed());
	}
	commandCrud.save(c);
	fixtureCrud.save(c->getFixture());
      }
    }
  }
}

SessionShared CommandsSchedulerController::getSession() const {
  return session;
}

void CommandsSchedulerController::setSession(const SessionShared& value) {
  session = value;
}

MqttDeviceCommandPublisherShared CommandsSchedulerController::getDeviceCommandPublisher() const {
  return deviceCommandPublisher;
}

void CommandsSchedulerController::setDeviceCommandPublisher(const MqttDeviceCommandPublisherShared& value) {
  deviceCommandPublisher = value;
}

QMqttClientShared CommandsSchedulerController::getMqttClient() const {
  return mqttClient;
}

void CommandsSchedulerController::setMqttClient(const QMqttClientShared& value) {
  mqttClient = value;
  connect(mqttClient.data(), &QMqttClient::connected, this, &CommandsSchedulerController::onMqttConnected);
  connect(mqttClient.data(), &QMqttClient::disconnected, this, &CommandsSchedulerController::onMqttDisconnected);
  if (mqttClient->state() == QMqttClient::Connected) {
    onMqttConnected();
  }
}

int CommandsSchedulerController::getTimerInterval() const {
  return timer.interval();
}

void CommandsSchedulerController::setTimerInterval(int interval) {
  timer.setSingleShot(false);
  timer.setInterval(interval);
}

} // namespace CommandsScheduler
} // namespace light
