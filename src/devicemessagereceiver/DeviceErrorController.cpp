#include "DeviceErrorController.h"

#include "AbstractDeviceErrorSaver.h"
#include "MqttDeviceErrorSubscriber.h"

namespace light {
namespace DeviceMessageReceiver {
DeviceErrorController::DeviceErrorController(QObject* parent)
  : QObject(parent) {
}

void DeviceErrorController::onDeviceErrorReceived(const DeviceError& error) {
  if (deviceErrorSaver)
    deviceErrorSaver->saveError(error);
}

MqttDeviceErrorSubscriberShared DeviceErrorController::getErrorSubscriber() const {
  return errorSubscriber;
}

void DeviceErrorController::setErrorSubscriber(const MqttDeviceErrorSubscriberShared& value) {
  errorSubscriber = value;
  connect(errorSubscriber.data(),
	  &MqttDeviceErrorSubscriber::deviceErrorReceived,
	  this,
	  &DeviceErrorController::onDeviceErrorReceived);
}

AbstractDeviceErrorSaverShared DeviceErrorController::getDeviceErrorSaver() const {
  return deviceErrorSaver;
}

void DeviceErrorController::setDeviceErrorSaver(const AbstractDeviceErrorSaverShared& value) {
  deviceErrorSaver = value;
}
} // namespace DeviceMessageReceiver
} // namespace light
