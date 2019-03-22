#include "MqttDeviceErrorSubscriber.h"

#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMqttClient>
#include <QMqttSubscription>

namespace light {
namespace DeviceMessageReceiver {
MqttDeviceErrorSubscriber::MqttDeviceErrorSubscriber(QObject* parent) : QObject(parent) {
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

void MqttDeviceErrorSubscriber::subscribe() {
  QMqttTopicFilter topicFilter{topic};
  subscription = mqttClient->subscribe(topic, 2);
  connect(subscription, &QMqttSubscription::messageReceived, this, &MqttDeviceErrorSubscriber::onMessageReceived);
}

QMqttClientShared MqttDeviceErrorSubscriber::getMqttClient() const {
  return mqttClient;
}

void MqttDeviceErrorSubscriber::setMqttClient(const QMqttClientShared& value) {
  mqttClient = value;
  connect(mqttClient.data(), &QMqttClient::connected, this, &MqttDeviceErrorSubscriber::subscribe);
  if (mqttClient->state() == QMqttClient::Connected) {
    subscribe();
  }
}

QString MqttDeviceErrorSubscriber::getTopic() const {
  return topic;
}

void MqttDeviceErrorSubscriber::setTopic(const QString& value) {
  topic = value;
}
} // namespace DeviceMessageReceiver
} // namespace light
