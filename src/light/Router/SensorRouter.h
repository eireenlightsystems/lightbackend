#ifndef SENSORROUTER_H
#define SENSORROUTER_H

#include "PostgresCrudSensor.h"
#include "PostgresCrudSensorType.h"
#include "RestRouter.h"
#include "Sensor.h"
#include "SensorController.h"
#include "SensorType.h"
#include "SimpleEditableRouter.h"
#include "SensorTypeToJson.h"

namespace light {

template <>
class RestRouter<Sensor> : public SimpleEditableRouter<Sensor>
{
public:
  QString getName() const override {
    return "sensors";
  }
};

template <>
class RestRouter<SensorType> : public SimpleSelectableRouter<SensorType>
{
public:
  QString getName() const override {
    return "sensors-types";
  }
};

} // namespace light

#endif // SENSORROUTER_H
