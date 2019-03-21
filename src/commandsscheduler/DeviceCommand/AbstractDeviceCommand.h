#ifndef ABSTRACTDEVICECOMMAND_H
#define ABSTRACTDEVICECOMMAND_H

#include "typedefs.h"

#include <QByteArray>
#include <QDateTime>

namespace light {

enum class CommandNumber : quint8
{
  None = 0,
  SpeedToLightUp = 1,
  SpeedToLightDown = 2,
  FixtureSwitchOn = 3,
  DeviceSwitchOff = 4
};

class AbstractDeviceCommand
{
public:
  AbstractDeviceCommand() = default;
  AbstractDeviceCommand(ulong gatewayId,
			quint8 firstNode,
			quint8 lastNode,
			quint8 deviceNumber,
			CommandNumber commandNumber);
  virtual ~AbstractDeviceCommand() = default;
  virtual QByteArray getRawData() const;
  virtual void fromRawData(const QByteArray &rawData) = 0;

  ulong getGatewayId() const;
  void setGatewayId(ulong value);

  quint8 getFirstNode() const;
  void setFirstNode(quint8 value);

  quint8 getLastNode() const;
  void setLastNode(quint8 value);

  CommandNumber getCommandNumber() const;
  void setCommandNumber(CommandNumber value);

  quint8 getDeviceNumber() const;
  void setDeviceNumber(const quint8& value);

  ID getCommandId() const;
  void setCommandId(const ID& value);

  QDateTime getDateTime() const;
  void setDateTime(const QDateTime& value);

private:
  ID commandId{0};
  QDateTime dateTime;
  ulong gatewayId{0};
  quint8 firstNode{0};
  quint8 lastNode{0};
  quint8 deviceNumber{0};
  CommandNumber commandNumber{CommandNumber::None};
};
} // namespace light

#endif // ABSTRACTDEVICECOMMAND_H
