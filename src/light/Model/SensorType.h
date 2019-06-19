#ifndef SENSORTYPE_H
#define SENSORTYPE_H

#include "EquipmentType.h"

namespace light {

class SensorType : public EquipmentType
{
public:
  SensorType() = default;

  double getDetectionRange() const;
  void setDetectionRange(double value);

private:
  double detectionRange;
};

} // namespace light

#endif // SENSORTYPE_H
