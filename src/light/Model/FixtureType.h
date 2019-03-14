#ifndef FIXTURETYPE_H
#define FIXTURETYPE_H

#include "EquipmentType.h"

namespace light {
class FixtureType : public EquipmentType
{
public:
  FixtureType() = default;
  ~FixtureType() override = default;

  double getLenght() const;
  void setLenght(double value);

  double getWidth() const;
  void setWidth(double value);

  double getHeight() const;
  void setHeight(double value);

  double getWeight() const;
  void setWeight(double value);

private:
  double lenght{0.0};
  double width{0.0};
  double height{0.0};
  double weight{0.0};
};
} // namespace light

#endif // FIXTURETYPE_H
