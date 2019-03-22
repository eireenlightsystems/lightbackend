#ifndef FIXTURECOMMAND_H
#define FIXTURECOMMAND_H

#include "AbstractDeviceCommand.h"
#include "CommandsSchedulerTypeDefs.h"

namespace light {
namespace CommandsScheduler {

class FixtureCommand : public AbstractDeviceCommand
{
public:
  FixtureCommand() = default;
  FixtureCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber,
		 CommandNumber commandNumber);

  SchedulerFixtureShared getFixture() const;
  ID getFixtureId() const;
  void setFixture(const SchedulerFixtureShared& value);

private:
  SchedulerFixtureShared fixture;
};

} // namespace CommandsScheduler
} // namespace light

#endif // FIXTURECOMMAND_H
