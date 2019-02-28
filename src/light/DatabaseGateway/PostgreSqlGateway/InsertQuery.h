#ifndef INSERTQUERY_H
#define INSERTQUERY_H

#include "SqlQuery.h"
#include "typedefs.h"

namespace light {
namespace PostgresqlGateway {
class InsertQuery : public SqlQuery
{
public:
  explicit InsertQuery(const QSqlDatabase& db);
  void exec() override;
  ID getInsertedId() const;

private:
  ID insertedId{0};
};
} // namespace PostgresqlGateway
} // namespace light

#endif // INSERTQUERY_H
