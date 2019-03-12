#ifndef SQLQUERY_H
#define SQLQUERY_H

#include "typedefs.h"

#include <QMap>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

using BindParamsType = QMap<QString, QVariant>;

class SqlQuery
{
public:
  explicit SqlQuery(const QSqlDatabase& db);
  virtual ~SqlQuery();
  SqlQuery(const SqlQuery& other);
  void prepare(const QString& sql);
  void bind(const QString& placeholder, const QVariant& value);
  void bind(const BindParamsType& params);
  virtual void exec();
  void execBatch();
  void finish();

protected:
  QSharedPointer<QSqlQuery> getQuery() const;
  void tryReconnect();

private:
  QSqlDatabase db;
  QSharedPointer<QSqlQuery> query;
};

QVariant idToVariant(ID id);

} // namespace PostgresqlGateway
} // namespace light

#endif // SQLQUERY_H
