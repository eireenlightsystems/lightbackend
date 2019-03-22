#ifndef MQTTDEVICEERRORSUBSCRIVER_H
#define MQTTDEVICEERRORSUBSCRIVER_H

#include "SharedTypes.h"

#include <QMqttMessage>
#include <QObject>

class QMqttClient;
class QMqttSubscription;
class QMqttTopicName;
class QByteArray;

namespace light {
namespace DeviceMessageReceiver {
class MqttDeviceErrorSubscriber : public QObject
{
  Q_OBJECT
public:
  explicit MqttDeviceErrorSubscriber(QObject* parent = nullptr);

  QString getTopic() const;
  void setTopic(const QString& value);

  QMqttClientShared getMqttClient() const;
  void setMqttClient(const QMqttClientShared& value);

signals:
  void deviceErrorReceived(const DeviceError& error);

private slots:
  void onMessageReceived(QMqttMessage msg);
  void subscribe();

private:
  QString topic;
  QMqttSubscription* subscription = nullptr;
  QMqttClientShared mqttClient;
};
} // namespace DeviceMessageReceiver
} // namespace light
#endif // MQTTDEVICEERRORSUBSCRIVER_H
