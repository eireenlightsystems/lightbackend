#include "Service.h"

namespace DeviceMessageReceiver {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Device Message Receiver") {
}

void Service::start()
{

}

} // namespace DeviceMessageReceiver
