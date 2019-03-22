#ifndef SCHEDULERFIXTURE_H
#define SCHEDULERFIXTURE_H

#include "typedefs.h"

namespace light {
namespace CommandsScheduler {

class SchedulerFixture
{
public:
  SchedulerFixture();

  ID getId() const;
  void setId(const ID& value);

  quint8 getStandbyLevel() const;
  void setStandbyLevel(const quint8& value);

  quint8 getWorkLevel() const;
  void setWorkLevel(const quint8& value);

  quint8 getSpeedUp() const;
  void setSpeedUp(const quint8& value);

  quint8 getSpeedDown() const;
  void setSpeedDown(const quint8& value);

private:
  ID id{0};
  quint8 standbyLevel{0};
  quint8 workLevel{0};
  quint8 speedUp{0};
  quint8 speedDown{0};
};
} // namespace CommandsScheduler
} // namespace light

#endif // SCHEDULERFIXTURE_H
