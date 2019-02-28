#ifndef SQLDATABASEOWNER_H
#define SQLDATABASEOWNER_H

#include "SelectQuery.h"

#include <QSqlDatabase>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {
class SqlDatabaseOwner
{
public:
  QSqlDatabase getDb() const;
  void setDb(const QSqlDatabase& value);

protected:
  template <typename T>
  T buildAndExecQuery(const QString& sql, const BindParamsType& bindParams) const {
    T query(db);
    query.prepare(sql);
    query.bind(bindParams);
    query.exec();
    return query;
  }

  template <typename T>
  T buildAndExecBatchQuery(const QString& sql, const BindParamsType& bindParams) const {
    T query(db);
    query.prepare(sql);
    query.bind(bindParams);
    query.execBatch();
    return query;
  }

  template <typename Collection, typename ParseFunction>
  Collection select(const QString& sql, const BindParamsType params, ParseFunction parseFunction) const {
    Collection result;
    auto query = buildAndExecQuery<SelectQuery>(sql, params);
    for (const auto& record : query) {
      result << parseFunction(record);
    }
    return result;
  }

private:
  QSqlDatabase db;
};
} // namespace PostgresqlGateway
} // namespace light

#endif // SQLDATABASEOWNER_H
