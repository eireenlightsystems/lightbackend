#include "AbstractDeviceCommand.h"

#include <QDataStream>

namespace light {
namespace CommandsScheduler {
AbstractDeviceCommand::AbstractDeviceCommand(ulong gatewayId,
					     quint8 firstNode,
					     quint8 lastNode,
					     quint8 deviceNumber,
					     CommandNumber commandNumber)
  : gatewayId(gatewayId)
  , firstNode(firstNode)
  , lastNode(lastNode)
  , deviceNumber(deviceNumber)
  , commandNumber(commandNumber) {
}

QByteArray AbstractDeviceCommand::getRawData() const {
  QByteArray rawData;
  QDataStream ds(&rawData, QIODevice::WriteOnly);
  ds.setByteOrder(QDataStream::BigEndian);

  ds << firstNode << lastNode << deviceNumber << static_cast<quint8>(commandNumber);

  return rawData;
}

ulong AbstractDeviceCommand::getGatewayId() const {
  return gatewayId;
}

void AbstractDeviceCommand::setGatewayId(ulong value) {
  gatewayId = value;
}

quint8 AbstractDeviceCommand::getFirstNode() const {
  return firstNode;
}

void AbstractDeviceCommand::setFirstNode(quint8 value) {
  firstNode = value;
}

quint8 AbstractDeviceCommand::getLastNode() const {
  return lastNode;
}

void AbstractDeviceCommand::setLastNode(quint8 value) {
  lastNode = value;
}

CommandNumber AbstractDeviceCommand::getCommandNumber() const {
  return commandNumber;
}

void AbstractDeviceCommand::setCommandNumber(CommandNumber value) {
  commandNumber = value;
}

quint8 AbstractDeviceCommand::getDeviceNumber() const {
  return deviceNumber;
}

void AbstractDeviceCommand::setDeviceNumber(const quint8& value) {
  deviceNumber = value;
}

ID AbstractDeviceCommand::getId() const {
  return Id;
}

void AbstractDeviceCommand::setId(const ID& value) {
  Id = value;
}

QDateTime AbstractDeviceCommand::getDateTime() const {
  return dateTime;
}

void AbstractDeviceCommand::setDateTime(const QDateTime& value) {
  dateTime = value;
}

CommandStatus AbstractDeviceCommand::getStatus() const {
  return status;
}

void AbstractDeviceCommand::setStatus(const CommandStatus& value) {
  status = value;
}
} // namespace CommandsScheduler
} // namespace light
