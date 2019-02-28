#include "SpeedToLightDownDeviceCommand.h"

namespace light {
SpeedToLightDownDeviceCommand::SpeedToLightDownDeviceCommand() {
  setCommandNumber(CommandNumber::SpeedToLightDown);
}

SpeedToLightDownDeviceCommand::SpeedToLightDownDeviceCommand(ulong gatewayId,
						 quint8 firstNode,
						 quint8 lastNode,
						 quint8 deviceNumber)
  : SpeedToLightBaseDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, CommandNumber::SpeedToLightDown) {
}
} // namespace light
