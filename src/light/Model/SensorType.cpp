#include "SensorType.h"

namespace light {

double SensorType::getDetectionRange() const {
  return detectionRange;
}

void SensorType::setDetectionRange(double value) {
  detectionRange = value;
}

} // namespace light

