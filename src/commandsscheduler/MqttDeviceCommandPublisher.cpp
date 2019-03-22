#include "MqttDeviceCommandPublisher.h"

#include "AbstractDeviceCommand.h"

#include <QMqttClient>

namespace light {
namespace CommandsScheduler {
MqttDeviceCommandPublisher::MqttDeviceCommandPublisher(QObject* parent) : QObject(parent) {
}

bool MqttDeviceCommandPublisher::publish(const AbstractDeviceCommandSharedList& commands) {
  if (mqttClient and mqttClient->state() == QMqttClient::Connected) {
    for (const auto& command : commands) {
      const QString fullTopic = QString("%1/%2").arg(topic, command->getGatewayId());
      auto rawCommandData = command->getRawData();
      mqttClient->publish(fullTopic, rawCommandData);
      qDebug() << mqttClient->state() << "publish to topic" << fullTopic << "data" << rawCommandData << "size"
	       << rawCommandData.size();
    }
    return true;
  }

  return false;
}

QString MqttDeviceCommandPublisher::getTopic() const {
  return topic;
}

void MqttDeviceCommandPublisher::setTopic(const QString& value) {
  topic = value;
}

QMqttClientShared MqttDeviceCommandPublisher::getMqttClient() const {
  return mqttClient;
}

void MqttDeviceCommandPublisher::setMqttClient(const QMqttClientShared& value) {
  mqttClient = value;
}
} // namespace CommandsScheduler
} // namespace light
