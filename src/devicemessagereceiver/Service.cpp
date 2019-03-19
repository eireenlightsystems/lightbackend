#include "Service.h"

#include "DeviceErrorController.h"

namespace DeviceMessageReceiver {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Device Message Receiver") {
}

void Service::start()
{
  deviceErrorController = DeviceErrorControllerShared::create();
  deviceErrorController->init();
}

} // namespace DeviceMessageReceiver
