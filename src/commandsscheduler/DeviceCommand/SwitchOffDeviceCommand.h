#ifndef SWITCHOFFDEVICECOMMAND_H
#define SWITCHOFFDEVICECOMMAND_H

#include "AbstractDeviceCommand.h"

namespace light {
namespace CommandsScheduler {
class SwitchOffDeviceCommand : public AbstractDeviceCommand
{
public:
  SwitchOffDeviceCommand();
  SwitchOffDeviceCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber);
};

} // namespace CommandsScheduler
} // namespace light
#endif // SWITCHOFFDEVICECOMMAND_H
