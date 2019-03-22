#ifndef MQTTDEVICECOMMANDPUBLISHER_H
#define MQTTDEVICECOMMANDPUBLISHER_H

#include "CommandsSchedulerTypeDefs.h"

#include <QObject>
#include <QSharedPointer>

class QMqttClient;

namespace light {
namespace CommandsScheduler {

class MqttDeviceCommandPublisher : public QObject
{
  Q_OBJECT
public:
  explicit MqttDeviceCommandPublisher(QObject* parent = nullptr);

  QMqttClientShared getMqttClient() const;
  void setMqttClient(const QMqttClientShared& value);

  QString getTopic() const;
  void setTopic(const QString& value);

public slots:
  bool publish(const AbstractDeviceCommandSharedList& commands);

private:
  QMqttClientShared mqttClient;
  QString topic;
};
} // namespace CommandsScheduler
} // namespace light

#endif // MQTTDEVICECOMMANDPUBLISHER_H
