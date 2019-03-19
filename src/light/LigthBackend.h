#ifndef LIGHTBACKEND_H
#define LIGHTBACKEND_H

#include "PostgresConnectionInfo.h"
#include "typedefs.h"

#include <QObject>

namespace light {

struct FixtureCommandsFilter;
struct NodeFilter;
class LigthBackend : public QObject
{
  Q_OBJECT
public:
  explicit LigthBackend(QObject* parent = nullptr);
  void init();
  FixtureLightLevelCommandSharedList
  getFixtureLightLevelCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const;
  FixtureLightSpeedCommandSharedList
  getFixtureLightSpeedCommandsByDateTimeRange(const FixtureCommandsFilter& filter) const;

  SessionShared getSession() const;

public slots:
  void switchOnFixtures(const FixtureLightLevelCommandSharedList& commands);
  void setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList& commands);
  void deleteFixturesCommands(const QList<ID>& commands);

private:
  void initDatabase();
  PostgresConnectionInfo readConnectionInfoFromSettings() const;
  void initInMemoryDb();
  void initPostgres();
  void initCommandController();
  void initFixtureCommandController();

private:
  DeviceCommandsControllerShared deviceCommandController;
  CommandsControllerShared fixturesCommandsController;
  SessionShared session;
};

} // namespace light
#endif // LIGHTBACKEND_H
