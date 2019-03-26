#include "Sensor.h"

#include "SensorType.h"

namespace light {

ID Sensor::getId() const {
  return id;
}

void Sensor::setId(const ID& value) {
  id = value;
}

SensorTypeShared Sensor::getType() const {
  return type;
}

ID Sensor::getTypeId() const {
  if (type)
    return type->getId();

  return 0;
}

void Sensor::setType(const SensorTypeShared& value) {
  type = value;
}

} // namespace light
