#include "FixtureSwitchOnDeviceCommand.h"

#include <QDataStream>
namespace light {

FixtureSwitchOnDeviceCommand::FixtureSwitchOnDeviceCommand() {
  setCommandNumber(CommandNumber::FixtureSwitchOn);
}

FixtureSwitchOnDeviceCommand::FixtureSwitchOnDeviceCommand(ulong gatewayId,
							   quint8 firstNode,
							   quint8 lastNode,
							   quint8 deviceNumber)
  : AbstractDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, CommandNumber::FixtureSwitchOn) {
}

QByteArray FixtureSwitchOnDeviceCommand::getRawData() const {
  QByteArray rawData = AbstractDeviceCommand::getRawData();
  QDataStream ds(&rawData, QIODevice::Append);
  ds << workLevel << standbyLevel;

  return rawData;
}

void FixtureSwitchOnDeviceCommand::fromRawData(const QByteArray& rawData) {
  QDataStream ds(rawData);
  ds.setByteOrder(QDataStream::BigEndian);
  quint8 firstNode, lastNode, deviceNumber, cn;
  ds >> firstNode >> lastNode >> deviceNumber >> cn >> workLevel >> standbyLevel;
  setCommandNumber(CommandNumber(cn));
  setFirstNode(firstNode);
  setLastNode(lastNode);
  setDeviceNumber(deviceNumber);
}

quint8 FixtureSwitchOnDeviceCommand::getWorkLevel() const {
  return workLevel;
}

void FixtureSwitchOnDeviceCommand::setWorkLevel(quint8 value) {
  workLevel = value;
}

quint8 FixtureSwitchOnDeviceCommand::getStandbyLevel() const {
  return standbyLevel;
}

void FixtureSwitchOnDeviceCommand::setStandbyLevel(quint8 value) {
  standbyLevel = value;
}
} // namespace light
