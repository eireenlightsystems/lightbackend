#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
QSqlDatabase SqlDatabaseOwner::getDb() const {
  return db;
}

void SqlDatabaseOwner::setDb(const QSqlDatabase& value) {
  db = value;
}
} // namespace PostgresqlGateway
} // namespace light
