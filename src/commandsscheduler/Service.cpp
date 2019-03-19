#include "Service.h"

#include "CommandsSchedulerController.h"

namespace CommandsScheduler {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Commands Scheduler") {
}

void Service::start() {
  controller = CommandsSchedulerControllerShared::create();
  controller->init();
}

} // namespace CommandsScheduler
