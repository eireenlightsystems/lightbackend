#ifndef FIXTURELIGHTLEVELCOMMAND_H
#define FIXTURELIGHTLEVELCOMMAND_H

#include "FixtureCommand.h"
#include "typedefs.h"

namespace light {
class FixtureLightLevelCommand : public FixtureCommand
{
public:
  FixtureLightLevelCommand() = default;
  ~FixtureLightLevelCommand() override = default;

  bool operator==(const FixtureLightLevelCommand& other);
  bool operator!=(const FixtureLightLevelCommand& other);

  quint8 getWorkLevel() const;
  void setWorkLevel(quint8 value);

  quint8 getStandbyLevel() const;
  void setStandbyLevel(quint8 value);

  void setLevels(quint8 wLevel, quint8 sLevel);

private:
  quint8 workLevel{0};
  quint8 standbyLevel{0};
};
} // namespace light

#endif // FIXTURELIGHTLEVELCOMMAND_H
