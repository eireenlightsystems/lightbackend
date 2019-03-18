#ifndef SERVICE_H
#define SERVICE_H

#include <qtservice.h>

namespace DeviceMessageReceiver {

class Service : public QtService<QCoreApplication>
{
public:
  Service(int argc, char** argv);
  ~Service() override = default;
  void start() override;
};

} // namespace DeviceMessageReceiver

#endif // SERVICE_H
