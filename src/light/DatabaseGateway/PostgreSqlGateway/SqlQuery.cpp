#include "SqlQuery.h"

#include "DatabaseException.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QSqlError>

namespace light {
namespace PostgresqlGateway {
SqlQuery::SqlQuery(const QSqlDatabase& db) : db(db) {
  query = QSharedPointer<QSqlQuery>::create(db);
}

SqlQuery::~SqlQuery() {
}

SqlQuery::SqlQuery(const SqlQuery& other) {
  this->query = other.query;
}

void SqlQuery::prepare(const QString& sql) {
//  qDebug() << sql;
  if (!query->prepare(sql)) {
    const QString errorText = query->lastError().text();
    tryReconnect();
    if (!query->prepare(sql)) {
      qCritical() << Q_FUNC_INFO << errorText;
      throw DatabaseException(errorText);
    }
  }
}

void SqlQuery::bind(const QString& placeholder, const QVariant& value) {
  query->bindValue(placeholder, value);
}

void SqlQuery::bind(const BindParamsType& params) {
  QMapIterator<QString, QVariant> it(params);
  while (it.hasNext()) {
    it.next();
    bind(it.key(), it.value());
  }
}

void SqlQuery::exec() {
  if (!query->exec()) {
    qCritical() << Q_FUNC_INFO << query->lastError().text();
    throw DatabaseException(query->lastError().text());
  }
}

void SqlQuery::execBatch() {
  if (!query->execBatch()) {
    qCritical() << Q_FUNC_INFO << query->lastError().text();
    throw DatabaseException(query->lastError().text());
  }
}

void SqlQuery::finish() {
  if (query)
    query->finish();
}

QSharedPointer<QSqlQuery> SqlQuery::getQuery() const {
  return query;
}

void SqlQuery::tryReconnect() {
  if (!db.isOpen())
    db.open();
}

QVariant idToVariant(ID id) {
  return id ? id : QVariant();
}

} // namespace PostgresqlGateway
} // namespace light
