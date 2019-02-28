#ifndef POSTGRESFIXTURELIGHTLEVELCOMMANDGATEWAY_H
#define POSTGRESFIXTURELIGHTLEVELCOMMANDGATEWAY_H

#include "AbstractFixtureCommandGateway.h"
#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
class PostgresFixtureLightLevelCommandGateway : public SqlDatabaseOwner, public AbstractFixtureLightLevelCommandGateway
{
public:
  PostgresFixtureLightLevelCommandGateway() = default;
  FixtureLightLevelCommandShared selectLightLevelCommand(ID id) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const QList<ID>& ids) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const QDateTime& dateTime) override;
  FixtureLightLevelCommandSharedList selectLightLevelCommands(const FixtureCommandsFilter& filter) override;
  void saveLightLevelCommand(const FixtureLightLevelCommandShared& command) override;
  void saveLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) override;
  void deleteLightLevelCommand(const FixtureLightLevelCommandShared& command) override;
  void deleteLightLevelCommands(const FixtureLightLevelCommandSharedList& commands) override;

private:
  FixtureLightLevelCommandSharedList selectBase(const QString& sql, const BindParamsType& params) const;
  FixtureLightLevelCommandShared parseLightLevelCommand(const QSqlRecord& record) const;
  void insertLightLevelCommand(const FixtureLightLevelCommandShared& command);
  void updateLightLevelCommand(const FixtureLightLevelCommandShared& command);
};
} // namespace PostgresqlGateway
} // namespace light
#endif // POSTGRESFIXTURELIGHTLEVELCOMMANDGATEWAY_H
