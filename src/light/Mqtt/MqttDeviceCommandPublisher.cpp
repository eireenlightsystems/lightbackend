#include "MqttDeviceCommandPublisher.h"

#include "AbstractDeviceCommand.h"

#include <QMqttClient>

namespace light {
MqttDeviceCommandPublisher::MqttDeviceCommandPublisher(QObject* parent) : QObject(parent) {
}

void MqttDeviceCommandPublisher::publish(const AbstractDeviceCommandSharedList& commands) {
  if (mqttClient) {
    for (const auto& command : commands) {
      const QString topic = QString("/gateway/%1").arg(command->getGatewayId());
      auto rawCommandData = command->getRawData();
      mqttClient->publish(topic, rawCommandData);
      qDebug() << mqttClient->state() << "publish to topic" << topic << "data" << rawCommandData << "size" << rawCommandData.size();
    }
  }
}

QMqttClientShared MqttDeviceCommandPublisher::getMqttClient() const {
  return mqttClient;
}

void MqttDeviceCommandPublisher::setMqttClient(const QMqttClientShared& value) {
  mqttClient = value;
}
} // namespace light
