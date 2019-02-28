#include "TestSchedulerGateway.h"

TestDeviceCommandGateway::~TestDeviceCommandGateway() {
}

light::AbstractDeviceCommandSharedList
TestDeviceCommandGateway::selectDeviceInCommandsInQueue(const QDateTime& dateTime) {
  Q_UNUSED(dateTime);
  return light::AbstractDeviceCommandSharedList();
}

void TestDeviceCommandGateway::saveDeviceCommands(const light::AbstractDeviceCommandSharedList& deviceCommands) {
  Q_UNUSED(deviceCommands);
}

QDateTime TestDeviceCommandGateway::getClosestDeviceCommandDateTime() {
  return closestDateTime;
}

void TestDeviceCommandGateway::setClosestDateTime(const QDateTime& value) {
  closestDateTime = value;
}
