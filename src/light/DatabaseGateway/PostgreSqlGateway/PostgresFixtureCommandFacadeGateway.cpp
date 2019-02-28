#include "PostgresFixtureCommandFacadeGateway.h"

#include <QDebug>
#include <QSqlError>

namespace light {
namespace PostgresqlGateway {
AbstractDeviceCommandSharedList
PostgresFixtureCommandFacadeGateway::selectDeviceInCommandsInQueue(const QDateTime& dateTime) {
  return deviceCommandGateway.selectDeviceInCommandsInQueue(dateTime);
}

void PostgresFixtureCommandFacadeGateway::saveDeviceCommands(const AbstractDeviceCommandSharedList& deviceCommands) {
  deviceCommandGateway.saveDeviceCommands(deviceCommands);
}

QDateTime PostgresFixtureCommandFacadeGateway::getClosestDeviceCommandDateTime() {
  return deviceCommandGateway.getClosestDeviceCommandDateTime();
}

FixtureLightSpeedCommandShared PostgresFixtureCommandFacadeGateway::selectLightSpeedCommand(ID id) {
  return fixtureLightSpeedCommandGateway.selectLightSpeedCommand(id);
}

FixtureLightSpeedCommandSharedList PostgresFixtureCommandFacadeGateway::selectLightSpeedCommands(const QList<ID>& ids) {
  return fixtureLightSpeedCommandGateway.selectLightSpeedCommands(ids);
}

FixtureLightSpeedCommandSharedList
PostgresFixtureCommandFacadeGateway::selectLightSpeedCommands(const QDateTime& dateTime) {
  return fixtureLightSpeedCommandGateway.selectLightSpeedCommands(dateTime);
}

FixtureLightSpeedCommandSharedList
PostgresFixtureCommandFacadeGateway::selectLightSpeedCommands(const FixtureCommandsFilter& filter) {
  return fixtureLightSpeedCommandGateway.selectLightSpeedCommands(filter);
}

void PostgresFixtureCommandFacadeGateway::saveLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  fixtureLightSpeedCommandGateway.saveLightSpeedCommand(command);
}

void PostgresFixtureCommandFacadeGateway::saveLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) {
  fixtureLightSpeedCommandGateway.saveLightSpeedCommands(commands);
}

void PostgresFixtureCommandFacadeGateway::deleteLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  fixtureLightSpeedCommandGateway.deleteLightSpeedCommand(command);
}

void PostgresFixtureCommandFacadeGateway::deleteLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) {
  fixtureLightSpeedCommandGateway.deleteLightSpeedCommands(commands);
}

FixtureLightLevelCommandShared PostgresFixtureCommandFacadeGateway::selectLightLevelCommand(ID id) {
  return fixtureLightLevelCommandGateway.selectLightLevelCommand(id);
}

FixtureLightLevelCommandSharedList PostgresFixtureCommandFacadeGateway::selectLightLevelCommands(const QList<ID>& ids) {
  return fixtureLightLevelCommandGateway.selectLightLevelCommands(ids);
}

FixtureLightLevelCommandSharedList
PostgresFixtureCommandFacadeGateway::selectLightLevelCommands(const QDateTime& dateTime) {
  return fixtureLightLevelCommandGateway.selectLightLevelCommands(dateTime);
}

FixtureLightLevelCommandSharedList
PostgresFixtureCommandFacadeGateway::selectLightLevelCommands(const FixtureCommandsFilter& filter) {
  return fixtureLightLevelCommandGateway.selectLightLevelCommands(filter);
}

void PostgresFixtureCommandFacadeGateway::saveLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  fixtureLightLevelCommandGateway.saveLightLevelCommand(command);
}

void PostgresFixtureCommandFacadeGateway::saveLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) {
  fixtureLightLevelCommandGateway.saveLightLevelCommands(commands);
}

void PostgresFixtureCommandFacadeGateway::deleteLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  fixtureLightLevelCommandGateway.deleteLightLevelCommand(command);
}

void PostgresFixtureCommandFacadeGateway::deleteLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) {
  fixtureLightLevelCommandGateway.deleteLightLevelCommands(commands);
}

FixtureCommandShared PostgresFixtureCommandFacadeGateway::selectCommand(ID id) {
  return fixtureCommandGateway.selectCommand(id);
}

FixtureCommandSharedList PostgresFixtureCommandFacadeGateway::selectCommands(const QList<ID>& ids) {
  return fixtureCommandGateway.selectCommands(ids);
}

void PostgresFixtureCommandFacadeGateway::deleteCommand(const FixtureCommandShared& command) {
  fixtureCommandGateway.deleteCommand(command);
}

void PostgresFixtureCommandFacadeGateway::deleteCommands(const FixtureCommandSharedList& commands) {
  fixtureCommandGateway.deleteCommands(commands);
}

FixtureShared PostgresFixtureCommandFacadeGateway::selectFixture(ID id) {
  return fixtureGateway.selectFixture(id);
}

FixtureSharedList PostgresFixtureCommandFacadeGateway::selectFixtures(const QList<ID>& ids) {
  return fixtureGateway.selectFixtures(ids);
}

void PostgresFixtureCommandFacadeGateway::saveFixture(const FixtureShared& fixture) {
  fixtureGateway.saveFixture(fixture);
}

void PostgresFixtureCommandFacadeGateway::saveFixtures(const FixtureSharedList& fixtures) {
  fixtureGateway.saveFixtures(fixtures);
}

void PostgresFixtureCommandFacadeGateway::deleteFixture(const FixtureShared& fixture) {
  fixtureGateway.deleteFixture(fixture);
}

void PostgresFixtureCommandFacadeGateway::deleteFixtures(const FixtureSharedList& fixtures) {
  fixtureGateway.deleteFixtures(fixtures);
}

bool PostgresFixtureCommandFacadeGateway::open(const PostgresConnectionInfo& connectionInfo) {
  db = QSqlDatabase::addDatabase("QPSQL", "main");
  db.setHostName(connectionInfo.hostName);
  db.setPort(connectionInfo.port);
  db.setDatabaseName(connectionInfo.databaseName);
  db.setUserName(connectionInfo.userName);
  db.setPassword(connectionInfo.password);
  if (!db.open()) {
    qCritical() << "database not open " << db.lastError().text();
    return false;
  }

  setDb();
  return true;
}

void PostgresFixtureCommandFacadeGateway::setDb() {
  QList<SqlDatabaseOwner*> dbOwners{
      &deviceCommandGateway,
      &fixtureLightSpeedCommandGateway,
      &fixtureLightLevelCommandGateway,
      &fixtureCommandGateway,
      &fixtureGateway,
  };

  for (auto dbOwner : dbOwners) {
    dbOwner->setDb(db);
  }
}
} // namespace PostgresqlGateway
} // namespace light
