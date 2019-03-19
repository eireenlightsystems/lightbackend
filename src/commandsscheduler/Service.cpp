#include "Service.h"

namespace CommandsScheduler {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Commands Scheduler") {
}

void Service::start() {
}

} // namespace CommandsScheduler
