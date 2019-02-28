#include "InsertQuery.h"

#include <QVariant>

namespace light {
namespace PostgresqlGateway {
InsertQuery::InsertQuery(const QSqlDatabase& db) : SqlQuery(db) {
}

void InsertQuery::exec() {
  SqlQuery::exec();
  if (getQuery()->next())
    insertedId = getQuery()->value(0).value<ID>();
}

ID InsertQuery::getInsertedId() const {
  return insertedId;
}
} // namespace PostgresqlGateway
} // namespace light
