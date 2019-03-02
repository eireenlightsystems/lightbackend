#ifndef LIGHTBACKEND_H
#define LIGHTBACKEND_H

#include "PostgresConnectionInfo.h"
#include "SharedTypes.h"
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
  void init(const QString& hostName, quint16 port);
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
  void initMqttClient(const QString& hostName, quint16 port);
  void initDatabase();
  PostgresConnectionInfo readConnectionInfoFromSettings() const;
  void initInMemoryDb();
  void initPostgres();
  void initErrorController();
  void initCommandController();
  void initFixtureCommandController();

private:
  QMqttClientShared mqttClient;
  DeviceErrorControllerShared devideErrorController;
  DeviceCommandsControllerShared deviceCommandController;
  CommandsControllerShared fixturesCommandsController;
  SchedulerGatewayShared schedulerGateway;
  AbstractDeviceErrorSaverShared deviceErrorSaver;
  SessionShared session;
};

} // namespace light
#endif // LIGHTBACKEND_H
