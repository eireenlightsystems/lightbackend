#include "AbstractDeviceCommandTestWrapper.h"

AbstractDeviceCommandTestWrapper::AbstractDeviceCommandTestWrapper(
    ulong gatewayId,
    quint8 firstNode,
    quint8 lastNode,
    quint8 deviceNumber,
    light::CommandsScheduler::CommandNumber commandNumber)
  : light::CommandsScheduler::AbstractDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, commandNumber) {
}

void AbstractDeviceCommandTestWrapper::fromRawData(const QByteArray& rawData) {
  Q_UNUSED(rawData)
}
