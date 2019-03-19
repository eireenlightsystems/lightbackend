#ifndef SERVICE_H
#define SERVICE_H

#include <qtservice.h>

namespace CommandsScheduler {

class Service : public QtService<QCoreApplication>
{
public:
  Service(int argc, char** argv);
  ~Service() override = default;
  void start() override;
};
} // namespace CommandsScheduler
#endif // SERVICE_H
