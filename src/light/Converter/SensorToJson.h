#ifndef SENSORTOJSON_H
#define SENSORTOJSON_H

#include "Sensor.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Sensor> : public ToJsonConverterTemplate<Sensor>
{
public:
  QJsonObject toJson(const SensorShared& sensor) const override;
};

template <>
class ToJsonConverter<SensorContract> : public ToJsonConverterTemplate<SensorContract>
{
public:
  QJsonObject toJson(const SensorContractShared& sensorContract) const override;
};

} // namespace light

#endif // SENSORTOJSON_H
