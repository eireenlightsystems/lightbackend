#ifndef SPEEDTOLIGHTUPDEVICECOMMAND_H
#define SPEEDTOLIGHTUPDEVICECOMMAND_H

#include "SpeedToLightBaseDeviceCommand.h"

namespace light {
class SpeedToLightUpDeviceCommand : public SpeedToLightBaseDeviceCommand
{
public:
  SpeedToLightUpDeviceCommand();
  SpeedToLightUpDeviceCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber);
};
} // namespace light

#endif // SPEEDTOLIGHTUPDEVICECOMMAND_H
