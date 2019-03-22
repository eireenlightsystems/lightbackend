#ifndef SERVICE_H
#define SERVICE_H

#include "CommandsSchedulerTypeDefs.h"

#include <qtservice.h>

namespace light {
namespace CommandsScheduler {

class Service : public QtService<QCoreApplication>
{
public:
  Service(int argc, char** argv);
  ~Service() override = default;
  void start() override;

private:
  CommandsSchedulerControllerShared controller;
};
} // namespace CommandsScheduler
} // namespace light
#endif // SERVICE_H
