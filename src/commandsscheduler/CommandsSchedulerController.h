#ifndef COMMANDSSCHEDULERCONTROLLER_H
#define COMMANDSSCHEDULERCONTROLLER_H

#include "CommandsSchedulerTypeDefs.h"
#include "PostgresConnectionInfo.h"

#include <QTimer>

namespace CommandsScheduler {

struct MqttConnectionInfo
{
  QString hostName;
  quint16 port;
  QString clientId;
};

class CommandsSchedulerController : public QObject
{
  Q_OBJECT
public:
  explicit CommandsSchedulerController(QObject* parent = nullptr);
  void init();

private slots:
  void onSchedulerTimeout();
  void onMqttConnected();

private:
  void initMqtt();
  MqttConnectionInfo readMqttConnectionInfoFromSettings() const;
  void initMqttClient(const MqttConnectionInfo& connectionInfo);
  QString getSettingsPath() const;
  void initTimer();
  int readIntervalFromSettings() const;
  void initDatabase();
  light::PostgresConnectionInfo readConnectionInfoFromSettings() const;

private:
  QMqttClientShared mqttClient;
  SchedulerGatewayShared schedulerGateway;
  MqttDeviceCommandPublisherShared deviceCommandPublisher;
  QTimer timer;
  light::PostgresqlGateway::PostgresFixtureCommandFacadeGatewayShared fixtureCommandFacade;
};

} // namespace CommandsScheduler

#endif // COMMANDSSCHEDULERCONTROLLER_H
