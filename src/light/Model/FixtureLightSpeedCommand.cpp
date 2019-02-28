#include "FixtureLightSpeedCommand.h"

namespace light {

quint8 FixtureLightSpeedCommand::getSpeed() const {
  return speed;
}

void FixtureLightSpeedCommand::setSpeed(const quint8& value) {
  speed = value;
}

FixtureLightSpeedCommand::FixtureLightSpeedDirectionType FixtureLightSpeedCommand::getDirectionType() const {
  return directionType;
}

void FixtureLightSpeedCommand::setDirectionType(const FixtureLightSpeedDirectionType& value) {
  directionType = value;
}

} // namespace light
