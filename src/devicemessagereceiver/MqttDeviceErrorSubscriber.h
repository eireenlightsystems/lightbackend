#ifndef MQTTDEVICEERRORSUBSCRIVER_H
#define MQTTDEVICEERRORSUBSCRIVER_H

#include "SharedTypes.h"

#include <QMqttMessage>
#include <QObject>

class QMqttClient;
class QMqttSubscription;
class QMqttTopicName;
class QByteArray;

namespace DeviceMessageReceiver {
class MqttDeviceErrorSubscriber : public QObject
{
  Q_OBJECT
public:
  explicit MqttDeviceErrorSubscriber(QObject* parent = nullptr);

  QString getTopic() const;
  void setTopic(const QString& value);

signals:
  void deviceErrorReceived(const DeviceError& error);

public slots:
  void subscribe(const QSharedPointer<QMqttClient>& mqttClient);

private slots:
  void onMessageReceived(QMqttMessage msg);

private:
  QString topic;
  QMqttSubscription* subscription = nullptr;
};

} // namespace light
#endif // MQTTDEVICEERRORSUBSCRIVER_H
