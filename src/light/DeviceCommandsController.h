#ifndef DEVICECOMMANDSCONTROLLER_H
#define DEVICECOMMANDSCONTROLLER_H

#include "typedefs.h"

#include <QObject>

namespace light {
class DeviceCommandsController : public QObject
{
  Q_OBJECT
public:
  explicit DeviceCommandsController(QObject* parent = nullptr);
//  void setMqttClient(const QMqttClientShared& mqttClient);
  void setCommandController(const CommandsControllerShared& commandController);

  QDateTime getCheckCommandDateTime() const;
//  CommandsSchedulerShared getCommandsWatchDog() const;
//  MqttDeviceCommandPublisherShared getDeviceCommandPublisher() const;

//  SchedulerGatewayShared getSchedulerGateway() const;
//  void setSchedulerGateway(const SchedulerGatewayShared &value);

public slots:
  void setFixturesLightLevel(const FixtureLightLevelCommandSharedList& commands);
  void setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList &commands);
  void deleteFixturesCommands(const QList<ID>& commands);

private slots:
  void onSchedulerTimeout(const QDateTime& datetime);

private:
  CommandsControllerShared commandController;
//  SchedulerGatewayShared schedulerGateway;
};
} // namespace light

#endif // DEVICECOMMANDSCONTROLLER_H
