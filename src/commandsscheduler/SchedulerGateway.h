#ifndef SCHEDULERGATEWAY_H
#define SCHEDULERGATEWAY_H

#include "typedefs.h"

namespace light {
namespace CommandsScheduler {
class SchedulerGateway
{
public:
  SchedulerGateway() = default;
  ~SchedulerGateway() = default;
  QDateTime getClosestCommandDateTime() const;
  void markAsSentCommandsByDateTime(const QDateTime& dateTime);

private:
  void markAsSentLightLevel(const QDateTime& dateTime);
  void markAsSentLightSpeed(const QDateTime& dateTime);

};
} // namespace CommandsScheduler
} // namespace light

#endif // SCHEDULERGATEWAY_H
