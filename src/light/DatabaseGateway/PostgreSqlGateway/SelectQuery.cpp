#include "SelectQuery.h"

namespace light {
namespace PostgresqlGateway {

SelectQuery::SelectQuery(const QSqlDatabase& db) : SqlQuery(db) {
}

SelectQuery::Iterator SelectQuery::begin() {
  return Iterator(getQuery());
}

SelectQuery::Iterator SelectQuery::end() {
  return Iterator();
}

} // namespace PostgresqlGateway
} // namespace light
