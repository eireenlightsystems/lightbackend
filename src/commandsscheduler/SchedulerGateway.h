#ifndef SCHEDULERGATEWAY_H
#define SCHEDULERGATEWAY_H

#include "typedefs.h"

namespace CommandsScheduler {
class SchedulerGateway
{
public:
  struct Gateways
  {
    light::AbstractFixtureGatewayShared fixtureGateway;
    light::AbstractFixtureLightLevelCommandGatewayShared lightLevelCommandGateway;
    light::AbstractFixtureLightSpeedCommandGatewayShared lightSpeedCommandGateway;
    light::AbstractDeviceCommandGatewayShared deviceCommandGateway;
  };

  SchedulerGateway() = default;
  ~SchedulerGateway() = default;
  QDateTime getClosestCommandDateTime() const;
  void markAsSentCommandsByDateTime(const QDateTime& dateTime);

  Gateways getGateways() const;
  void setGateways(const Gateways& value);

private:
  void markAsSentLightLevel(const QDateTime& dateTime);
  void markAsSentLightSpeed(const QDateTime& dateTime);

private:
  Gateways gateways;
};
} // namespace CommandsScheduler

#endif // SCHEDULERGATEWAY_H
