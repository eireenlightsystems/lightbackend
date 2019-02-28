#ifndef SPEEDTOLIGHTBASEDEVICECOMMAND_H
#define SPEEDTOLIGHTBASEDEVICECOMMAND_H

#include "AbstractDeviceCommand.h"

namespace light {
class SpeedToLightBaseDeviceCommand : public AbstractDeviceCommand
{
public:
  SpeedToLightBaseDeviceCommand() = default;
  SpeedToLightBaseDeviceCommand(ulong gatewayId,
			  quint8 firstNode,
			  quint8 lastNode,
			  quint8 deviceNumber,
			  CommandNumber commandNumber);
  QByteArray getRawData() const override;
  void fromRawData(const QByteArray& rawData) override;

  quint8 getSpeed() const;
  void setSpeed(const quint8& value);

private:
  quint8 speed;
};
} // namespace light

#endif // SPEEDTOLIGHTBASEDEVICECOMMAND_H
