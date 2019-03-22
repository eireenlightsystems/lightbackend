#include "SwitchOffDeviceCommand.h"

namespace light {
namespace CommandsScheduler {
SwitchOffDeviceCommand::SwitchOffDeviceCommand() {
  setCommandNumber(CommandNumber::DeviceSwitchOff);
}

SwitchOffDeviceCommand::SwitchOffDeviceCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber)
  : AbstractDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, CommandNumber::DeviceSwitchOff) {
}
} // namespace CommandsScheduler
} // namespace light
