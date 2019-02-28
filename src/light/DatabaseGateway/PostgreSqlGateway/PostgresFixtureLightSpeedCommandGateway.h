#ifndef POSTGRESFIXTURELIGHTSPEEDCOMMANDGATEWAY_H
#define POSTGRESFIXTURELIGHTSPEEDCOMMANDGATEWAY_H

#include "AbstractFixtureCommandGateway.h"
#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
class PostgresFixtureLightSpeedCommandGateway : public SqlDatabaseOwner, public AbstractFixtureLightSpeedCommandGateway
{
public:
  PostgresFixtureLightSpeedCommandGateway() = default;
  FixtureLightSpeedCommandShared selectLightSpeedCommand(ID id) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QList<ID>& ids) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const QDateTime& dateTime) override;
  FixtureLightSpeedCommandSharedList selectLightSpeedCommands(const FixtureCommandsFilter& filter) override;
  void saveLightSpeedCommand(const FixtureLightSpeedCommandShared& command) override;
  void saveLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) override;
  void deleteLightSpeedCommand(const FixtureLightSpeedCommandShared& command) override;
  void deleteLightSpeedCommands(const FixtureLightSpeedCommandSharedList& commands) override;

private:
  FixtureLightSpeedCommandSharedList selectBase(const QString & sql, const BindParamsType& params) const;
  FixtureLightSpeedCommandShared parseLightSpeedCommand(const QSqlRecord& record) const;
  void insertLightSpeedCommand(const FixtureLightSpeedCommandShared& command);
  void updateLightSpeedCommand(const FixtureLightSpeedCommandShared& command);
};
} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESFIXTURELIGHTSPEEDCOMMANDGATEWAY_H
