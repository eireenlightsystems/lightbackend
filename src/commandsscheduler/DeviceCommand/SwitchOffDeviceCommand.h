#ifndef SWITCHOFFDEVICECOMMAND_H
#define SWITCHOFFDEVICECOMMAND_H

#include "AbstractDeviceCommand.h"

namespace light {

class SwitchOffDeviceCommand : public AbstractDeviceCommand
{
public:
  SwitchOffDeviceCommand();
  SwitchOffDeviceCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber);
};

} // namespace light

#endif // SWITCHOFFDEVICECOMMAND_H
