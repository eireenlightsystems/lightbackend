#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QMap>
#include <QSharedPointer>
#include <QSqlQuery>

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

protected:
  QSharedPointer<QSqlQuery> getQuery() const;
  void tryReconnect();

private:
  QSqlDatabase db;
  QSharedPointer<QSqlQuery> query;
};
} // namespace PostgresqlGateway
} // namespace light

#endif // SQLQUERY_H
