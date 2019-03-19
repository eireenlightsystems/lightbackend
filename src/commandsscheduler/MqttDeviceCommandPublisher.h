#ifndef MQTTDEVICECOMMANDPUBLISHER_H
#define MQTTDEVICECOMMANDPUBLISHER_H

#include "CommandsSchedulerTypeDefs.h"

#include <QObject>
#include <QSharedPointer>

class QMqttClient;

namespace CommandsScheduler {

class MqttDeviceCommandPublisher : public QObject
{
  Q_OBJECT
public:
  explicit MqttDeviceCommandPublisher(QObject* parent = nullptr);

  QMqttClientShared getMqttClient() const;
  void setMqttClient(const QMqttClientShared& value);

public slots:
  void publish(const light::AbstractDeviceCommandSharedList& commands);

private:
  QMqttClientShared mqttClient;
};
} // namespace CommandsScheduler

#endif // MQTTDEVICECOMMANDPUBLISHER_H
