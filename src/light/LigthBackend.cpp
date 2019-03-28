#include "LigthBackend.h"

#include "BadCredentials.h"
#include "Session.h"

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDebug>
#include <QSettings>

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
  connectionInfo = readConnectionInfoFromSettings();

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

SessionShared LigthBackend::getSession(const QString& token) const {
  return sessions.value(token);
}

bool LigthBackend::isLoggedIn(const QString& token) const {
  return sessions.contains(token);
}

QString LigthBackend::login(const QString& login, const QString& password) {
  QByteArray data;
  data.append(login + password);
  QString token = QString(QCryptographicHash::hash(data, QCryptographicHash::Sha512).toHex());

  if (sessions.contains(token)) {
    return token;
  }

  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", token);
  db.setHostName(connectionInfo.hostName);
  db.setPort(connectionInfo.port);
  db.setDatabaseName(connectionInfo.databaseName);
  db.setUserName(login);
  db.setPassword(password);
  if (!db.open()) {
    throw BadCredentialsException();
  }

  auto newSession = SessionShared::create();
  newSession->setDb(db);
  sessions.insert(token, newSession);
  return token;
}

void LigthBackend::logout(const QString& token) {
  sessions.remove(token);
}

} // namespace light
