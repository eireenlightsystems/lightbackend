#ifndef POSTGRESFIXTURECOMMANDGATEWAY_H
#define POSTGRESFIXTURECOMMANDGATEWAY_H

#include "AbstractFixtureCommandGateway.h"
#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
class PostgresFixtureCommandGateway : public SqlDatabaseOwner, public AbstractFixtureCommandGateway
{
public:
  PostgresFixtureCommandGateway();
  FixtureCommandShared selectCommand(ID id) override;
  FixtureCommandSharedList selectCommands(const QList<ID> &ids) override;
  void deleteCommand(const FixtureCommandShared& command) override;
  void deleteCommands(const FixtureCommandSharedList &commands) override;

private:
  FixtureCommandSharedList selectBase(const QString& sql, const BindParamsType& params) const;
  FixtureCommandShared parseFixtureCommand(const QSqlRecord& record) const;
};
} // namespace PostgresqlGateway
} // namespace light
#endif // POSTGRESFIXTURECOMMANDGATEWAY_H
