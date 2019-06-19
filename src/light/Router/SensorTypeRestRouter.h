#ifndef SENSORTYPERESTROUTE_H
#define SENSORTYPERESTROUTE_H

#include "SensorType.h"
#include "SensorTypeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudSensorType.h"

namespace light {

template <>
class RestRouter<SensorType> : public SimpleEditableRouter<SensorType>
{
public:
  QString getName() const override {
    return "sensors-types";
  }
};

}
#endif // SENSORTYPERESTROUTE_H
