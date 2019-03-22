#include "FixtureCommand.h"

#include "SchedulerFixture.h"

namespace light {
namespace CommandsScheduler {

FixtureCommand::FixtureCommand(ulong gatewayId,
			       quint8 firstNode,
			       quint8 lastNode,
			       quint8 deviceNumber,
			       CommandNumber commandNumber)
  : AbstractDeviceCommand(gatewayId, firstNode, lastNode, deviceNumber, commandNumber) {
}

SchedulerFixtureShared FixtureCommand::getFixture() const {
  return fixture;
}

ID FixtureCommand::getFixtureId() const {
  if (fixture)
    return fixture->getId();

  return 0;
}

void FixtureCommand::setFixture(const SchedulerFixtureShared& value) {
  fixture = value;
}

} // namespace CommandsScheduler
} // namespace light
