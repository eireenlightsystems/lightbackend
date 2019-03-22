#include "Service.h"

#include "DeviceErrorController.h"
#include "DeviceErrorControllerBuilder.h"

namespace light {
namespace DeviceMessageReceiver {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Device Message Receiver") {
}

void Service::start() {
  DeviceErrorControllerBuilder builder;
  deviceErrorController = builder.build();
}

} // namespace DeviceMessageReceiver
} // namespace light
