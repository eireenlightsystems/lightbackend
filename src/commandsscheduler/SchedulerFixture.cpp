#include "SchedulerFixture.h"

namespace light {
namespace CommandsScheduler {

SchedulerFixture::SchedulerFixture() {
}

ID SchedulerFixture::getId() const {
  return id;
}

void SchedulerFixture::setId(const ID& value) {
  id = value;
}

quint8 SchedulerFixture::getStandbyLevel() const {
  return standbyLevel;
}

void SchedulerFixture::setStandbyLevel(const quint8& value) {
  standbyLevel = value;
}

quint8 SchedulerFixture::getWorkLevel() const {
  return workLevel;
}

void SchedulerFixture::setWorkLevel(const quint8& value) {
  workLevel = value;
}

quint8 SchedulerFixture::getSpeedUp() const {
  return speedUp;
}

void SchedulerFixture::setSpeedUp(const quint8& value) {
  speedUp = value;
}

quint8 SchedulerFixture::getSpeedDown() const {
  return speedDown;
}

void SchedulerFixture::setSpeedDown(const quint8& value) {
  speedDown = value;
}

} // namespace CommandsScheduler
} // namespace light
