#ifndef SENSORROUTER_H
#define SENSORROUTER_H

#include "PostgresCrudSensor.h"
#include "PostgresCrudSensorType.h"
#include "RestRouter.h"
#include "Sensor.h"
#include "SensorController.h"
#include "SensorType.h"
#include "SensorTypeToJson.h"
#include "SimpleEditableRouter.h"

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
class RestRouter<SensorContract> : public SimpleSelectableRouter<SensorContract>
{
public:
  QString getName() const override {
    return "sensors-contracts";
  }
};

template <>
class RestRouter<SensorOwner> : public SimpleSelectableRouter<SensorOwner>
{
public:
  QString getName() const override {
    return "sensors-owners";
  }
};

} // namespace light

#endif // SENSORROUTER_H
