#include "CommandsSchedulerController.h"

#include "MqttDeviceCommandPublisher.h"
#include "PostgresFixtureCommandFacadeGateway.h"
#include "SchedulerGateway.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QMqttClient>
#include <QSettings>

namespace CommandsScheduler {

CommandsSchedulerController::CommandsSchedulerController(QObject* parent)
  : QObject(parent)
  , mqttClient(QMqttClientShared::create())
  , schedulerGateway(SchedulerGatewayShared::create())
  , deviceCommandPublisher(MqttDeviceCommandPublisherShared::create()) {
  connect(&timer, &QTimer::timeout, this, &CommandsSchedulerController::onSchedulerTimeout);
}

void CommandsSchedulerController::init() {
  initMqtt();
  initTimer();
  initDatabase();
}

void CommandsSchedulerController::onSchedulerTimeout() {
  auto closestDatetime = schedulerGateway->getClosestCommandDateTime();
  auto currentDatetime = QDateTime::currentDateTime();
  if (closestDatetime <= currentDatetime) {
    auto commands = fixtureCommandFacade->selectDeviceInCommandsInQueue(closestDatetime);
    deviceCommandPublisher->publish(commands);
    schedulerGateway->markAsSentCommandsByDateTime(closestDatetime);
  }
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
  return qApp->applicationDirPath() + "/lightbackend.conf";
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
  fixtureCommandFacade = light::PostgresqlGateway::PostgresFixtureCommandFacadeGatewayShared::create();
  auto connectionInfo = readConnectionInfoFromSettings();
  fixtureCommandFacade->open(connectionInfo);
  SchedulerGateway::Gateways gateways;
  gateways.fixtureGateway = fixtureCommandFacade;
  gateways.deviceCommandGateway = fixtureCommandFacade;
  gateways.lightLevelCommandGateway = fixtureCommandFacade;
  gateways.lightSpeedCommandGateway = fixtureCommandFacade;
  schedulerGateway->setGateways(gateways);
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

} // namespace CommandsScheduler
