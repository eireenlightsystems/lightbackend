#ifndef COMMANDSSCHEDULERTYPEDEFS_H
#define COMMANDSSCHEDULERTYPEDEFS_H

#include "typedefs.h"

DeclareShared(QMqttClient);

namespace CommandsScheduler {
using ID = light::ID;

DeclareShared(SchedulerGateway);
DeclareShared(MqttDeviceCommandPublisher);
DeclareShared(CommandsSchedulerController);

} // namespace CommandsScheduler

#endif // COMMANDSSCHEDULERTYPEDEFS_H
