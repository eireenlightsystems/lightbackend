#include "MqttDeviceErrorSubscriber.h"

#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMqttClient>
#include <QMqttSubscription>

namespace light {
MqttDeviceErrorSubscriber::MqttDeviceErrorSubscriber(QObject* parent) : QObject(parent) {
}

void MqttDeviceErrorSubscriber::subscribe(const QSharedPointer<QMqttClient>& mqttClient) {
  QMqttTopicFilter topicFilter{topic};
  subscription = mqttClient->subscribe(topic, 2);
  connect(subscription, &QMqttSubscription::messageReceived, this, &MqttDeviceErrorSubscriber::onMessageReceived);
}

void MqttDeviceErrorSubscriber::onMessageReceived(QMqttMessage msg) {
  qDebug() << msg.topic() << msg.payload();
  QDataStream ds(msg.payload());
  quint16 gatewayId;
  quint8 nodeNumber;
  quint8 deviceNumber;
  quint8 errorCode;

  ds >> gatewayId >> nodeNumber >> deviceNumber >> errorCode;

  qDebug() << "gatewayId" << gatewayId << "nodeNumber" << nodeNumber << "deviceNumber" << deviceNumber << "errorCode"
	   << errorCode;
  DeviceError error{gatewayId, nodeNumber, deviceNumber, errorCode};
  emit deviceErrorReceived(error);
}

QString MqttDeviceErrorSubscriber::getTopic() const {
  return topic;
}

void MqttDeviceErrorSubscriber::setTopic(const QString& value) {
  topic = value;
}
} // namespace light
