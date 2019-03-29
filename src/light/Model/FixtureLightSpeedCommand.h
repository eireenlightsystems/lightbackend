#ifndef FIXTURELIGHTSPEEDCOMMAND_H
#define FIXTURELIGHTSPEEDCOMMAND_H

#include "FixtureCommand.h"

namespace light {

class FixtureLightSpeedCommandType : public FixtureCommandType
{
public:
  FixtureLightSpeedCommandType() = default;
  ~FixtureLightSpeedCommandType() override = default;
  explicit FixtureLightSpeedCommandType(const FixtureCommandType& other) : FixtureCommandType(other) {
  }
};

class FixtureLightSpeedCommand : public FixtureCommand
{
public:
  enum class FixtureLightSpeedDirectionType
  {
    None = 0,
    StandbyToWork = 4,
    WorkToStandby = 5
  };
  FixtureLightSpeedCommand() = default;
  ~FixtureLightSpeedCommand() override = default;

  quint8 getSpeed() const;
  void setSpeed(const quint8& value);

  FixtureLightSpeedDirectionType getDirectionType() const;
  void setDirectionType(const FixtureLightSpeedDirectionType& value);

private:
  FixtureLightSpeedDirectionType directionType = FixtureLightSpeedDirectionType::None;
  quint8 speed;
};
} // namespace light

#endif // FIXTURELIGHTSPEEDCOMMAND_H
