#include "DeviceErrorControllerBuilder.h"

#include "DeviceErrorController.h"
#include "MqttDeviceErrorSubscriber.h"
#include "PostgresDeviceErrorSaver.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMqttClient>
#include <QSettings>

namespace light {
namespace DeviceMessageReceiver {

DeviceErrorControllerShared DeviceErrorControllerBuilder::build() {
  auto dbConnectionSettings = readDbConnectionInfoFromSettings();
  auto mqttConnectionSettings = readMqttConnectionInfoFromSettings();
  auto topic = readSubscriberTopicFromSettings();

  auto errorSaver = PostgresDeviceErrorSaverShared::create();
  errorSaver->open(dbConnectionSettings);

  auto mqttClient = QMqttClientShared::create();
  mqttClient->setHostname(mqttConnectionSettings.hostName);
  mqttClient->setPort(mqttConnectionSettings.port);
  mqttClient->setClientId(mqttConnectionSettings.clientId);
  mqttClient->setCleanSession(false);
  mqttClient->connectToHost();

  auto subscriber = MqttDeviceErrorSubscriberShared::create();
  subscriber->setTopic(topic);
  subscriber->setMqttClient(mqttClient);

  auto controller = DeviceErrorControllerShared::create();
  controller->setDeviceErrorSaver(errorSaver);
  controller->setErrorSubscriber(subscriber);

  return controller;
}

PostgresConnectionInfo DeviceErrorControllerBuilder::readDbConnectionInfoFromSettings() const {
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

MqttConnectionInfo DeviceErrorControllerBuilder::readMqttConnectionInfoFromSettings() const {
  MqttConnectionInfo connectionInfo;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Mqtt");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").value<quint16>();
  connectionInfo.clientId = settings.value("clientId").toString();
  settings.endGroup();

  return connectionInfo;
}

QString DeviceErrorControllerBuilder::readSubscriberTopicFromSettings() const {
  QString topic;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Mqtt");
  topic = settings.value("subscriberTopic").toString();
  settings.endGroup();

  return topic;
}

QString DeviceErrorControllerBuilder::getSettingsPath() const {
  return qApp->applicationDirPath() + "/devicemessagereceiver.conf";
}

} // namespace DeviceMessageReceiver
} // namespace light
