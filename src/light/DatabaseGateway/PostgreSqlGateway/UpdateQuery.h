#ifndef UPDATEQUERY_H
#define UPDATEQUERY_H

#include "SqlQuery.h"

namespace light {
namespace PostgresqlGateway {
class UpdateQuery : public SqlQuery
{
public:
  explicit UpdateQuery(const QSqlDatabase& db);
};
} // namespace PostgresqlGateway
} // namespace light

#endif // UPDATEQUERY_H
