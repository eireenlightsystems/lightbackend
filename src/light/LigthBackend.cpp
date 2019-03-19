#include "LigthBackend.h"

#include "CommandsController.h"
#include "DeviceCommandsController.h"
#include "InMemoryDatabaseGateway.h"
#include "PostgresFixtureCommandFacadeGateway.h"
#include "Session.h"

#include <QCoreApplication>
#include <QMqttClient>
#include <QSettings>

namespace light {
LigthBackend::LigthBackend(QObject* parent) : QObject(parent) {
}

void LigthBackend::init() {
  initFixtureCommandController();
  initDatabase();
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

void LigthBackend::initDatabase() {
//  schedulerGateway = SchedulerGatewayShared::create();
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

  qDebug() << connectionInfo.hostName << connectionInfo.port << connectionInfo.databaseName << connectionInfo.userName;

  return connectionInfo;
}

void LigthBackend::initInMemoryDb() {
  auto inMemoryGateway = InMemoryDatabaseGatewayShared::create();
  fixturesCommandsController->setFixtureCommandGateway(inMemoryGateway);
//  schedulerGateway->setGateways({inMemoryGateway, inMemoryGateway, inMemoryGateway, inMemoryGateway});
}

void LigthBackend::initPostgres() {
  const PostgresConnectionInfo connectionInfo = readConnectionInfoFromSettings();
  auto fixtureCommandGateway = PostgresqlGateway::PostgresFixtureCommandFacadeGatewayShared::create();
  if (!fixtureCommandGateway->open(connectionInfo)) {
    qApp->quit();
  }
  fixturesCommandsController->setFixtureCommandGateway(fixtureCommandGateway);
//  schedulerGateway->setGateways(
//      {fixtureCommandGateway, fixtureCommandGateway, fixtureCommandGateway, fixtureCommandGateway});

  session = SessionShared::create();
  session->setDb(fixtureCommandGateway->getDb());
}

void LigthBackend::initCommandController() {
  deviceCommandController = DeviceCommandsControllerShared::create();
//  deviceCommandController->setMqttClient(mqttClient);
  deviceCommandController->setCommandController(fixturesCommandsController);
//  deviceCommandController->setSchedulerGateway(schedulerGateway);
}

void LigthBackend::initFixtureCommandController() {
  fixturesCommandsController = CommandsControllerShared::create();
}

SessionShared LigthBackend::getSession() const
{
  return session;
}

} // namespace light
