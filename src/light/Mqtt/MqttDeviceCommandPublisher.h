#ifndef MQTTDEVICECOMMANDPUBLISHER_H
#define MQTTDEVICECOMMANDPUBLISHER_H

#include "AbstractDeviceCommand.h"
#include "typedefs.h"

#include <QObject>
#include <QSharedPointer>

class QMqttClient;

namespace light {

class MqttDeviceCommandPublisher : public QObject
{
  Q_OBJECT
public:
  explicit MqttDeviceCommandPublisher(QObject* parent = nullptr);

  QMqttClientShared getMqttClient() const;
  void setMqttClient(const QMqttClientShared& value);

public slots:
  void publish(const AbstractDeviceCommandSharedList& commands);

private:
  QMqttClientShared mqttClient;
};
} // namespace light

#endif // MQTTDEVICECOMMANDPUBLISHER_H
