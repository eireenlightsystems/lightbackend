#include "LigthBackend.h"

#include "AbstractDeviceErrorSaver.h"
#include "CommandsController.h"
#include "DeviceCommandsController.h"
#include "DeviceErrorController.h"
#include "InMemoryDatabaseGateway.h"
#include "PostgresDeviceErrorSaver.h"
#include "PostgresFixtureCommandFacadeGateway.h"
#include "SchedulerGateway.h"
#include "Session.h"

#include <QCoreApplication>
#include <QMqttClient>
#include <QSettings>

namespace light {
LigthBackend::LigthBackend(QObject* parent) : QObject(parent) {
}

void LigthBackend::init(const QString& hostName, quint16 port) {
  initMqttClient(hostName, port);
  initFixtureCommandController();
  initDatabase();
  initErrorController();
  initCommandController();
}

FixtureLightLevelCommandSharedList
LigthBackend::getFixtureLightLevelCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const {
  return fixturesCommandsController->getFixtureLightLevelCommandsByDateTimeRange(filter);
}

FixtureLightSpeedCommandSharedList
LigthBackend::getFixtureLightSpeedCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const {
  return fixturesCommandsController->getFixtureLightSpeedCommandsByDateTimeRange(filter);
}

void LigthBackend::switchOnFixtures(const FixtureLightLevelCommandSharedList& commands) {
  deviceCommandController->setFixturesLightLevel(commands);
}

void LigthBackend::setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList& commands) {
  deviceCommandController->setFixturesLightSpeed(commands);
}

void LigthBackend::deleteFixturesCommands(const QList<ID>& commands) {
  deviceCommandController->deleteFixturesCommands(commands);
}

void LigthBackend::initMqttClient(const QString& hostName, quint16 port) {
  mqttClient = QMqttClientShared::create();
  mqttClient->setHostname(hostName);
  mqttClient->setPort(port);
  mqttClient->setClientId("DatabaseProvider");
  mqttClient->setCleanSession(false);
  mqttClient->connectToHost();
}

void LigthBackend::initDatabase() {
  schedulerGateway = SchedulerGatewayShared::create();
  //  initInMemoryDb();
  initPostgres();
}

PostgresConnectionInfo LigthBackend::readConnectionInfoFromSettings() const {
  PostgresConnectionInfo connectionInfo;

  QSettings settings(qApp->applicationDirPath() + "/lightbackend.conf", QSettings::IniFormat);
  settings.beginGroup("Database");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").toInt();
  connectionInfo.databaseName = settings.value("databaseName").toString();
  connectionInfo.userName = settings.value("username").toString();
  connectionInfo.password = settings.value("password").toString();
  settings.endGroup();

  return connectionInfo;
}

void LigthBackend::initInMemoryDb() {
  auto inMemoryGateway = InMemoryDatabaseGatewayShared::create();
  fixturesCommandsController->setFixtureCommandGateway(inMemoryGateway);
  schedulerGateway->setGateways({inMemoryGateway, inMemoryGateway, inMemoryGateway, inMemoryGateway});
}

void LigthBackend::initPostgres() {
  const PostgresConnectionInfo connectionInfo = readConnectionInfoFromSettings();
  auto fixtureCommandGateway = PostgresqlGateway::PostgresFixtureCommandFacadeGatewayShared::create();
  if (!fixtureCommandGateway->open(connectionInfo)) {
    qApp->quit();
  }
  fixturesCommandsController->setFixtureCommandGateway(fixtureCommandGateway);
  schedulerGateway->setGateways(
      {fixtureCommandGateway, fixtureCommandGateway, fixtureCommandGateway, fixtureCommandGateway});

  auto postgresDeviceErrorSaver = PostgresDeviceErrorSaverShared::create();
  if (!postgresDeviceErrorSaver->open(connectionInfo)) {
    qApp->quit();
  }
  deviceErrorSaver = postgresDeviceErrorSaver;
  session = SessionShared::create();
  session->setDb(fixtureCommandGateway->getDb());
}

void LigthBackend::initErrorController() {
  devideErrorController = DeviceErrorControllerShared::create();
  devideErrorController->setMqttCilent(mqttClient);
  devideErrorController->setDeviceErrorSaver(deviceErrorSaver);
}

void LigthBackend::initCommandController() {
  deviceCommandController = DeviceCommandsControllerShared::create();
  deviceCommandController->setMqttClient(mqttClient);
  deviceCommandController->setCommandController(fixturesCommandsController);
  deviceCommandController->setSchedulerGateway(schedulerGateway);
}

void LigthBackend::initFixtureCommandController() {
  fixturesCommandsController = CommandsControllerShared::create();
}

SessionShared LigthBackend::getSession() const
{
  return session;
}

} // namespace light
