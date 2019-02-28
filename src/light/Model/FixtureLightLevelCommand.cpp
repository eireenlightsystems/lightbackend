#include "FixtureLightLevelCommand.h"

namespace light {
bool FixtureLightLevelCommand::operator==(const FixtureLightLevelCommand& other) {
  return getCommandId() != other.getCommandId();
}

bool FixtureLightLevelCommand::operator!=(const FixtureLightLevelCommand& other) {
  return !this->operator==(other);
}

quint8 FixtureLightLevelCommand::getWorkLevel() const {
  return workLevel;
}

void FixtureLightLevelCommand::setWorkLevel(quint8 value) {
  workLevel = qMin(value, quint8(100));
  if(workLevel < standbyLevel) {
    setStandbyLevel(workLevel);
  }
}

quint8 FixtureLightLevelCommand::getStandbyLevel() const {
  return standbyLevel;
}

void FixtureLightLevelCommand::setStandbyLevel(quint8 value) {
  standbyLevel = qMin(value, quint8(100));
  if(standbyLevel > workLevel) {
    setWorkLevel(standbyLevel);
  }
}

void FixtureLightLevelCommand::setLevels(quint8 wLevel, quint8 sLevel)
{
  setWorkLevel(wLevel);
  setStandbyLevel(sLevel);
}
} // namespace light
