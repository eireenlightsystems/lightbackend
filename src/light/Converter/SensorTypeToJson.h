#ifndef SENSORTYPETOJSON_H
#define SENSORTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<SensorType> : public ToJsonConverterTemplate<SensorType>
{
public:
  QJsonObject toJson(const SensorTypeShared& sensorType) const override;
};

} // namespace light

#endif // SENSORTYPETOJSON_H
