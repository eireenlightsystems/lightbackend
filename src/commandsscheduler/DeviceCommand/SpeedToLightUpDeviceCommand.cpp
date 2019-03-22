#include "SpeedToLightUpDeviceCommand.h"

namespace light {
namespace CommandsScheduler {
SpeedToLightUpDeviceCommand::SpeedToLightUpDeviceCommand() {
  setCommandNumber(CommandNumber::SpeedToLightUp);
}

SpeedToLightUpDeviceCommand::SpeedToLightUpDeviceCommand(ulong gatewayId,
							 quint8 firstNode,
							 quint8 lastNode,
							 quint8 deviceNumber)
  : SpeedToLightBaseDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, CommandNumber::SpeedToLightUp) {
}
} // namespace CommandsScheduler
} // namespace light
