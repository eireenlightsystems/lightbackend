#include "CommandsSchedulerController.h"

#include "FixtureSwitchOnDeviceCommandPostgresCrud.h"
#include "MqttDeviceCommandPublisher.h"
#include "SchedulerFixture.h"
#include "SchedulerGateway.h"
#include "SpeedToLightBaseDeviceCommandPostgresCrud.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QMqttClient>
#include <QSettings>

namespace light {
namespace CommandsScheduler {

CommandsSchedulerController::CommandsSchedulerController(QObject* parent)
  : QObject(parent)
  , mqttClient(QMqttClientShared::create())
  , deviceCommandPublisher(MqttDeviceCommandPublisherShared::create()) {
  connect(&timer, &QTimer::timeout, this, &CommandsSchedulerController::onSchedulerTimeout);
}

void CommandsSchedulerController::init() {
  initMqtt();
  initTimer();
  initDatabase();
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

void CommandsSchedulerController::initMqtt() {
  auto connectionInfo = readMqttConnectionInfoFromSettings();
  initMqttClient(connectionInfo);
  connect(mqttClient.data(), &QMqttClient::connected, this, &CommandsSchedulerController::onMqttConnected);
}

MqttConnectionInfo CommandsSchedulerController::readMqttConnectionInfoFromSettings() const {
  MqttConnectionInfo connectionInfo;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Mqtt");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").value<quint16>();
  connectionInfo.clientId = settings.value("commandSchedulerClientId").toString();
  settings.endGroup();

  return connectionInfo;
}

void CommandsSchedulerController::initMqttClient(const MqttConnectionInfo& connectionInfo) {
  mqttClient->setHostname(connectionInfo.hostName);
  mqttClient->setPort(connectionInfo.port);
  mqttClient->setClientId(connectionInfo.clientId);
  mqttClient->setCleanSession(false);
  mqttClient->connectToHost();
}

QString CommandsSchedulerController::getSettingsPath() const {
  return qApp->applicationDirPath() + "/commandsscheduler.conf";
}

void CommandsSchedulerController::initTimer() {
  auto interval = readIntervalFromSettings();
  timer.setSingleShot(false);
  timer.setInterval(interval);
}

int CommandsSchedulerController::readIntervalFromSettings() const {
  int interval;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Scheduler");
  interval = settings.value("interval").toInt();
  settings.endGroup();

  return interval;
}

void CommandsSchedulerController::initDatabase() {
  session = SessionShared::create();
  auto connectionInfo = readConnectionInfoFromSettings();
}

light::PostgresConnectionInfo CommandsSchedulerController::readConnectionInfoFromSettings() const {
  light::PostgresConnectionInfo connectionInfo;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Database");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").toInt();
  connectionInfo.databaseName = settings.value("databaseName").toString();
  connectionInfo.userName = settings.value("username").toString();
  connectionInfo.password = settings.value("password").toString();
  settings.endGroup();

  qDebug() << connectionInfo.hostName << connectionInfo.port << connectionInfo.databaseName << connectionInfo.userName;

  return connectionInfo;
}

void CommandsSchedulerController::publishSwitchOnCommand(const QDateTime& datetime) {
  PostgresqlGateway::PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand> crud;
  crud.setSession(session);
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
      }
    }
  }
}

void CommandsSchedulerController::publishSpeedCommand(const QDateTime& datetime) {
  PostgresqlGateway::PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand> crud;
  crud.setSession(session);
  const QVariantHash params{
      {"dateTime", datetime},
  };
  auto speedCommands = crud.sel(params);
  if (speedCommands.count()) {
    for (auto c : speedCommands) {
      if (deviceCommandPublisher->publish({c})) {
	auto fixture = c->getFixture();
	if (c->getCommandNumber() == CommandNumber::SpeedToLightUp) {
	  fixture->setSpeedUp(c->getSpeed());
	} else if (c->getCommandNumber() == CommandNumber::SpeedToLightDown) {
	  fixture->setSpeedDown(c->getSpeed());
	}
	crud.save(c);
      }
    }
  }
}

} // namespace CommandsScheduler
} // namespace light
