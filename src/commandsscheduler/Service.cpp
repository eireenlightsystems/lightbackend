#include "Service.h"

#include "CommandsSchedulerController.h"
#include "CommandsSchedulerControllerBuilder.h"

namespace light {
namespace CommandsScheduler {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Commands Scheduler") {
}

void Service::start() {
  CommandsSchedulerControllerBuilder controllerBuilder;
  controller = controllerBuilder.build();
}

} // namespace CommandsScheduler
} // namespace light
