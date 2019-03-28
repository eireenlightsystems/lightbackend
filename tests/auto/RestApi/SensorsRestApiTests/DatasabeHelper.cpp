#include "DatasabeHelper.h"

#include <QSqlQuery>

DatasabeHelper::DatasabeHelper() {
}

bool DatasabeHelper::openDatabase(const QString& hostName,
				  int port,
				  const QString& databaseName,
				  const QString& username,
				  const QString& password) {
  db = QSqlDatabase::addDatabase("QPSQL", "tests");
  db.setHostName(hostName);
  db.setPort(port);
  db.setDatabaseName(databaseName);
  db.setUserName(username);
  db.setPassword(password);
  return db.open();
}

QVariant
DatasabeHelper::extractValue(const QString& table, const QString& field, const QString& idField, qulonglong id) {
  QString sql = QString("select %1 from %2 where %3 = :id").arg(field, table, idField);
  QSqlQuery query(db);
  query.prepare(sql);
  query.bindValue(":id", id);
  if (!query.exec())
    return QVariant();

  if(!query.next())
    return QVariant();

  return query.value(field);
}
