#include "DeleteQuery.h"

namespace light {
namespace PostgresqlGateway {
DeleteQuery::DeleteQuery(const QSqlDatabase& db) : SqlQuery(db) {
}
} // namespace PostgresqlGateway
} // namespace light
