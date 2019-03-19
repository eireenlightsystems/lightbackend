#ifndef SERVICE_H
#define SERVICE_H

#include "DeviceMessageReceiverTypeDefs.h"
#include <qtservice.h>

namespace DeviceMessageReceiver {

class Service : public QtService<QCoreApplication>
{
public:
  Service(int argc, char** argv);
  ~Service() override = default;
  void start() override;

private:
  DeviceErrorControllerShared deviceErrorController;
};

} // namespace DeviceMessageReceiver

#endif // SERVICE_H
