#include "SpeedToLightDownDeviceCommand.h"

namespace light {
namespace CommandsScheduler {
SpeedToLightDownDeviceCommand::SpeedToLightDownDeviceCommand() {
  setCommandNumber(CommandNumber::SpeedToLightDown);
}

SpeedToLightDownDeviceCommand::SpeedToLightDownDeviceCommand(ulong gatewayId,
							     quint8 firstNode,
							     quint8 lastNode,
							     quint8 deviceNumber)
  : SpeedToLightBaseDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, CommandNumber::SpeedToLightDown) {
}
} // namespace CommandsScheduler
} // namespace light
