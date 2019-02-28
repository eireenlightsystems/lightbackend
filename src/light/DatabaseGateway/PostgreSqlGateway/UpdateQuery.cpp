#include "UpdateQuery.h"

namespace light {
namespace PostgresqlGateway {
UpdateQuery::UpdateQuery(const QSqlDatabase& db) : SqlQuery(db) {
}
} // namespace PostgresqlGateway
} // namespace light
