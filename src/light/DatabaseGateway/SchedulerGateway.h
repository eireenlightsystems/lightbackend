#ifndef SCHEDULERGATEWAY_H
#define SCHEDULERGATEWAY_H

#include "typedefs.h"

namespace light {
class SchedulerGateway
{
public:
  struct Gateways
  {
    AbstractFixtureGatewayShared fixtureGateway;
    AbstractFixtureLightLevelCommandGatewayShared lightLevelCommandGateway;
    AbstractFixtureLightSpeedCommandGatewayShared lightSpeedCommandGateway;
    AbstractDeviceCommandGatewayShared deviceCommandGateway;
  };

  SchedulerGateway() = default;
  ~SchedulerGateway() = default;
  QDateTime getClosestCommandDateTime() const;
  void markAsSentCommandsByDateTime(const QDateTime& dateTime);

  Gateways getGateways() const;
  void setGateways(const Gateways &value);

private:
  void markAsSentLightLevel(const QDateTime& dateTime);
  void markAsSentLightSpeed(const QDateTime& dateTime);

private:
  Gateways gateways;
};
} // namespace light

#endif // SCHEDULERGATEWAY_H
