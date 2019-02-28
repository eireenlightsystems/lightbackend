#ifndef DELETEQUERY_H
#define DELETEQUERY_H

#include "SqlQuery.h"

namespace light {
namespace PostgresqlGateway {
class DeleteQuery : public SqlQuery
{
public:
  explicit DeleteQuery(const QSqlDatabase& db);
};
} // namespace PostgresqlGateway
} // namespace light

#endif // DELETEQUERY_H
