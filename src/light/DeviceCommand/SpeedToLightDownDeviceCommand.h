#ifndef SPEEDTOLIGHTDOWNDEVICECOMMAND_H
#define SPEEDTOLIGHTDOWNDEVICECOMMAND_H

#include "SpeedToLightBaseDeviceCommand.h"

namespace light {

class SpeedToLightDownDeviceCommand : public SpeedToLightBaseDeviceCommand
{
public:
  SpeedToLightDownDeviceCommand();
  SpeedToLightDownDeviceCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber);
};
} // namespace light

#endif // SPEEDTOLIGHTDOWNDEVICECOMMAND_H
