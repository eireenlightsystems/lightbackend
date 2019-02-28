#ifndef POSTGRESFIXTUREGATEWAY_H
#define POSTGRESFIXTUREGATEWAY_H

#include "AbstractFixtureCommandGateway.h"
#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
class PostgresFixtureGateway : public SqlDatabaseOwner, public AbstractFixtureGateway
{
public:
  PostgresFixtureGateway() = default;
  ~PostgresFixtureGateway() override = default;
  FixtureShared selectFixture(ID id) override;
  FixtureSharedList selectFixtures(const QList<ID>& ids) override;
  void saveFixture(const FixtureShared& fixture) override;
  void saveFixtures(const FixtureSharedList& fixtures) override;
  void deleteFixture(const FixtureShared& fixture) override;
  void deleteFixtures(const FixtureSharedList& fixtures) override;

private:
  FixtureSharedList selectBase(const QString& sql, const BindParamsType& params) const;
  FixtureShared parseFixture(const QSqlRecord& record) const;
  void insertFixture(const FixtureShared& fixture);
  void updateFixture(const FixtureShared& fixture);
};
} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESFIXTUREGATEWAY_H
