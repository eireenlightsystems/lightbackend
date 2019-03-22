#include "CommandsSchedulerControllerBuilder.h"

#include "CommandsSchedulerController.h"
#include "MqttDeviceCommandPublisher.h"
#include "Session.h"

#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QMqttClient>
#include <QSqlDatabase>

namespace light {
namespace CommandsScheduler {

CommandsSchedulerControllerShared CommandsSchedulerControllerBuilder::build() {
  auto dbConnectionSettings = readDbConnectionInfoFromSettings();
  auto mqttConnectionSettings = readMqttConnectionInfoFromSettings();
  auto interval = readIntervalFromSettings();
  auto topic = readPublisherTopicFromSettings();

  auto mqttClient = QMqttClientShared::create();
  mqttClient->setHostname(mqttConnectionSettings.hostName);
  mqttClient->setPort(mqttConnectionSettings.port);
  mqttClient->setClientId(mqttConnectionSettings.clientId);
  mqttClient->setCleanSession(false);
  mqttClient->connectToHost();

  auto publisher = MqttDeviceCommandPublisherShared::create();
  publisher->setTopic(topic);
  publisher->setMqttClient(mqttClient);

  auto session = SessionShared::create();
  auto db = QSqlDatabase::addDatabase("QPSQL", "light");
  db.setHostName(dbConnectionSettings.hostName);
  db.setPort(dbConnectionSettings.port);
  db.setDatabaseName(dbConnectionSettings.databaseName);
  db.setUserName(dbConnectionSettings.userName);
  db.setPassword(dbConnectionSettings.password);
  db.open();
  session->setDb(db);

  auto controller = CommandsSchedulerControllerShared::create();
  controller->setDeviceCommandPublisher(publisher);
  controller->setMqttClient(mqttClient);
  controller->setSession(session);
  controller->setTimerInterval(interval);

  return controller;
}

MqttConnectionInfo CommandsSchedulerControllerBuilder::readMqttConnectionInfoFromSettings() const {
  MqttConnectionInfo connectionInfo;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Mqtt");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").value<quint16>();
  connectionInfo.clientId = settings.value("clientId").toString();
  settings.endGroup();

  return connectionInfo;
}

PostgresConnectionInfo CommandsSchedulerControllerBuilder::readDbConnectionInfoFromSettings() const {
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

int CommandsSchedulerControllerBuilder::readIntervalFromSettings() const {
  int interval;

  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Timer");
  interval = settings.value("interval").toInt();
  settings.endGroup();

  return interval;
}

QString CommandsSchedulerControllerBuilder::readPublisherTopicFromSettings() const {
  QString topic;
  QSettings settings(getSettingsPath(), QSettings::IniFormat);
  settings.beginGroup("Mqtt");
  topic = settings.value("publisherTopic").toString();
  settings.endGroup();
  return topic;
}

QString CommandsSchedulerControllerBuilder::getSettingsPath() const {
  return qApp->applicationDirPath() + "/commandsscheduler.conf";
}

} // namespace CommandsScheduler
} // namespace light
