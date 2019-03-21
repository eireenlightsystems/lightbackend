#include "LigthBackend.h"

#include "Session.h"

#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

namespace light {
LigthBackend::LigthBackend(QObject* parent) : QObject(parent) {
}

void LigthBackend::init() {
  initDatabase();
}

void LigthBackend::initDatabase() {
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

void LigthBackend::initPostgres() {
  const PostgresConnectionInfo connectionInfo = readConnectionInfoFromSettings();

  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "light");
  db.setHostName(connectionInfo.hostName);
  db.setPort(connectionInfo.port);
  db.setDatabaseName(connectionInfo.databaseName);
  db.setUserName(connectionInfo.userName);
  db.setPassword(connectionInfo.password);
  db.open();
  session = SessionShared::create();
  session->setDb(db);
}

SessionShared LigthBackend::getSession() const {
  return session;
}

} // namespace light
