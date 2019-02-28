#include "DeviceErrorController.h"

#include "AbstractDeviceErrorSaver.h"
#include "MqttDeviceErrorSubscriber.h"

#include <QMqttClient>

namespace light {
DeviceErrorController::DeviceErrorController(QObject* parent)
  : QObject(parent), errorSubscriber(new MqttDeviceErrorSubscriber) {
  errorSubscriber->setTopic("/devices/error");
  connect(errorSubscriber.data(),
	  &MqttDeviceErrorSubscriber::deviceErrorReceived,
	  this,
	  &DeviceErrorController::onDeviceErrorReceived);
}

QMqttClientShared DeviceErrorController::getMqttCilent() const {
  return mqttClient;
}

void DeviceErrorController::setMqttCilent(const QMqttClientShared& value) {
  mqttClient = value;
  connect(mqttClient.data(), &QMqttClient::connected, this, &DeviceErrorController::onMqttConnected);
}

void DeviceErrorController::onMqttConnected() {
  errorSubscriber->subscribe(mqttClient);
}

void DeviceErrorController::onDeviceErrorReceived(const DeviceError& error) {
  if (deviceErrorSaver)
    deviceErrorSaver->saveError(error);
}

AbstractDeviceErrorSaverShared DeviceErrorController::getDeviceErrorSaver() const {
  return deviceErrorSaver;
}

void DeviceErrorController::setDeviceErrorSaver(const AbstractDeviceErrorSaverShared& value) {
  deviceErrorSaver = value;
}
} // namespace light
