#ifndef COMMANDSSCHEDULERTYPEDEFS_H
#define COMMANDSSCHEDULERTYPEDEFS_H

#include "typedefs.h"

DeclareShared(QMqttClient);

namespace light {
namespace CommandsScheduler {

DeclareShared(SchedulerFixture);
DeclareShared(SchedulerGateway);
DeclareShared(MqttDeviceCommandPublisher);
DeclareShared(CommandsSchedulerController);

DeclareShared(AbstractDeviceCommand);
DeclareShared(FixtureSwitchOnDeviceCommand);
DeclareShared(SpeedToLightBaseDeviceCommand);
DeclareShared(SpeedToLightUpDeviceCommand);
DeclareShared(SpeedToLightDownDeviceCommand);

} // namespace CommandsScheduler
}
#endif // COMMANDSSCHEDULERTYPEDEFS_H
