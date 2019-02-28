#ifndef TESTSCHEDULERGATEWAY_H
#define TESTSCHEDULERGATEWAY_H

#include <AbstractFixtureCommandGateway.h>
#include <SchedulerGateway.h>

class TestDeviceCommandGateway : public light::AbstractDeviceCommandGateway
{
public:
  TestDeviceCommandGateway() = default;
  ~TestDeviceCommandGateway() override;
  light::AbstractDeviceCommandSharedList selectDeviceInCommandsInQueue(const QDateTime& dateTime) override;
  void saveDeviceCommands(const light::AbstractDeviceCommandSharedList& deviceCommands) override;
  QDateTime getClosestDeviceCommandDateTime() override;

  void setClosestDateTime(const QDateTime& value);

private:
  QDateTime closestDateTime;
};

#endif // TESTSCHEDULERGATEWAY_H
