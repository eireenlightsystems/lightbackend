#ifndef FIXTURETYPE_H
#define FIXTURETYPE_H

#include "EquipmentType.h"

namespace light {
class FixtureType : public EquipmentType
{
public:
  FixtureType() = default;
  ~FixtureType() override = default;

  double getHeight() const;
  void setHeight(double value);

  double getWidth() const;
  void setWidth(double value);

  double getWeight() const;
  void setWeight(double value);

  double getLength() const;
  void setLength(double value);


  double getCountlamp() const;
  void setCountlamp(double value);

  double getPower() const;
  void setPower(double value);

  double getCos() const;
  void setCos(double value);

  double getIp() const;
  void setIp(double value);

  double getEfficiency() const;
  void setEfficiency(double value);

private:
  double height{0.0};
  double width{0.0};
  double weight{0.0};
  double length{0.0};

  double countlamp{0.0};
  double power{0.0};
  double cos{0.0};
  double ip{0.0};
  double efficiency{0.0};
};
} // namespace light

#endif // FIXTURETYPE_H
