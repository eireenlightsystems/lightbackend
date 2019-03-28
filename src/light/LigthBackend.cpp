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
  connectionInfo = readConnectionInfoFromSettings();
}

PostgresConnectionInfo LigthBackend::readConnectionInfoFromSettings() const {
  PostgresConnectionInfo connectionInfo;

  QSettings settings(qApp->applicationDirPath() + "/lightbackend.conf", QSettings::IniFormat);
  settings.beginGroup("Database");
  connectionInfo.hostName = settings.value("hostName").toString();
  connectionInfo.port = settings.value("port").toInt();
  connectionInfo.databaseName = settings.value("databaseName").toString();
  settings.endGroup();

  qDebug() << connectionInfo.hostName << connectionInfo.port << connectionInfo.databaseName;

  return connectionInfo;
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
  auto session = sessions[token];
  session->getDb().close();
  sessions.remove(token);
}

} // namespace light
