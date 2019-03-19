#include "DeviceErrorController.h"

#include "MqttDeviceErrorSubscriber.h"
#include "PostgresDeviceErrorSaver.h"

#include <QCoreApplication>
#include <QMqttClient>
#include <QSettings>

namespace DeviceMessageReceiver {
DeviceErrorController::DeviceErrorController(QObject* parent)
  : QObject(parent)
  , deviceErrorSaver(PostgresDeviceErrorSaverShared::create())
  , errorSubscriber(MqttDeviceErrorSubscriberShared::create())
  , mqttClient(QMqttClientShared::create()) {
}

void DeviceErrorController::init() {
  initSubscriber();
  initDatabase();
  initMqtt();
}

void DeviceErrorController::onMqttConnected() {
  errorSubscriber->subscribe(mqttClient);
}

void DeviceErrorController::onDeviceErrorReceived(const DeviceError& error) {
  if (deviceErrorSaver)
    deviceErrorSaver->saveError(error);
}

void DeviceErrorController::initSubscriber() {
  errorSubscriber->setTopic("/devices/error");
  connect(errorSubscriber.data(),
	  &MqttDeviceErrorSubscriber::deviceErrorReceived,
	  this,
	  &DeviceErrorController::onDeviceErrorReceived);
}

void DeviceErrorController::initDatabase() {
  auto postgresConnectionInfo = readConnectionInfoFromSettings();
  deviceErrorSaver->open(postgresConnectionInfo);
}

void DeviceErrorController::initMqtt() {
  auto connectionInfo = readMqttConnectionInfoFromSettings();
  initMqttClient(connectionInfo);
  connect(mqttClient.data(), &QMqttClient::connected, this, &DeviceErrorController::onMqttConnected);
}

light::PostgresConnectionInfo DeviceErrorController::readConnectionInfoFromSettings() const {
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

void DeviceErrorController::initMqttClient(const MqttConnectionInfo& connectionInfo) {
  mqttClient->setHostname(connectionInfo.hostName);
  mqttClient->setPort(connectionInfo.port);
  mqttClient->setClientId(connectionInfo.clientId);
  mqttClient->setCleanSession(false);
  mqttClient->connectToHost();
}

MqttConnectionInfo DeviceErrorController::readMqttConnectionInfoFromSettings() const {
  MqttConnectionInfo connectionInfo;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Mqtt");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").value<quint16>();
  connectionInfo.clientId = settings.value("deviceMessageReceiverClientId").toString();
  settings.endGroup();

  return connectionInfo;
}

QString DeviceErrorController::getSettingsPath() const {
  return qApp->applicationDirPath() + "/lightbackend.conf";
}
} // namespace DeviceMessageReceiver
