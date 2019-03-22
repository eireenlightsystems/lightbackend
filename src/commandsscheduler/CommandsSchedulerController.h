#ifndef COMMANDSSCHEDULERCONTROLLER_H
#define COMMANDSSCHEDULERCONTROLLER_H

#include "CommandsSchedulerTypeDefs.h"
#include "PostgresConnectionInfo.h"

#include <QTimer>

namespace light {
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
  void publishSwitchOnCommand(const QDateTime& datetime);
  void publishSpeedCommand(const QDateTime& datetime);

private:
  QMqttClientShared mqttClient;
  MqttDeviceCommandPublisherShared deviceCommandPublisher;
  QTimer timer;
  SessionShared session;
};
} // namespace CommandsScheduler
} // namespace light

#endif // COMMANDSSCHEDULERCONTROLLER_H
