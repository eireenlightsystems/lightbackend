#include "SpeedToLightBaseDeviceCommand.h"

#include <QDataStream>

namespace light {
SpeedToLightBaseDeviceCommand::SpeedToLightBaseDeviceCommand(ulong gatewayId,
							     quint8 firstNode,
							     quint8 lastNode,
							     quint8 deviceNumber,
							     CommandNumber commandNumber)
  : AbstractDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, commandNumber), speed{0} {
}

QByteArray SpeedToLightBaseDeviceCommand::getRawData() const {
  QByteArray rawData = AbstractDeviceCommand::getRawData();
  QDataStream ds(&rawData, QIODevice::Append);
  ds.setByteOrder(QDataStream::BigEndian);
  ds << speed;

  return rawData;
}

void SpeedToLightBaseDeviceCommand::fromRawData(const QByteArray& rawData) {
  QDataStream ds(rawData);
  ds.setByteOrder(QDataStream::BigEndian);
  quint8 firstNode, lastNode, deviceNumber, cn;
  ds >> firstNode >> lastNode >> deviceNumber >> cn >> speed;
  setCommandNumber(CommandNumber(cn));
  setFirstNode(firstNode);
  setLastNode(lastNode);
  setDeviceNumber(deviceNumber);
}

quint8 SpeedToLightBaseDeviceCommand::getSpeed() const {
  return speed;
}

void SpeedToLightBaseDeviceCommand::setSpeed(const quint8& value) {
  speed = value;
}
} // namespace light
