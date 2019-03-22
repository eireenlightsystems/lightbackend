#ifndef COMMANDSSCHEDULERCONTROLLER_H
#define COMMANDSSCHEDULERCONTROLLER_H

#include "CommandsSchedulerTypeDefs.h"
#include "MqttConnectionInfo.h"
#include "PostgresConnectionInfo.h"

#include <QTimer>

namespace light {
namespace CommandsScheduler {

class CommandsSchedulerController : public QObject
{
  Q_OBJECT
public:
  explicit CommandsSchedulerController(QObject* parent = nullptr);

  PostgresConnectionInfo getPostgresConnectionInfo() const;
  void setPostgresConnectionInfo(const PostgresConnectionInfo& value);

  MqttConnectionInfo getMqttConnectionInfo() const;
  void setMqttConnectionInfo(const MqttConnectionInfo& value);

  int getTimerInterval() const;
  void setTimerInterval(int interval);

  QMqttClientShared getMqttClient() const;
  void setMqttClient(const QMqttClientShared& value);

  MqttDeviceCommandPublisherShared getDeviceCommandPublisher() const;
  void setDeviceCommandPublisher(const MqttDeviceCommandPublisherShared& value);

  SessionShared getSession() const;
  void setSession(const SessionShared& value);

private slots:
  void onSchedulerTimeout();
  void onMqttConnected();
  void onMqttDisconnected();

private:
  void initTimer();
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
