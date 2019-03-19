#include "CommandsSchedulerController.h"

#include "MqttDeviceCommandPublisher.h"
#include "SchedulerGateway.h"

#include <QCoreApplication>
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
}

void CommandsSchedulerController::onSchedulerTimeout() {
  //  auto commands = commandController->getDeviceCommandsByDateTime(datetime);
  //  deviceCommandPublisher->publish(commands);
  //  schedulerGateway->markAsSentCommandsByDateTime(datetime);
  //  scheduler->checkUpdates();
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

} // namespace CommandsScheduler
