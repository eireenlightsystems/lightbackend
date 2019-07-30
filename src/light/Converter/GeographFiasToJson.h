#ifndef GEOGRAPHFIASTOJSON_H
#define GEOGRAPHFIASTOJSON_H


#include "GeographFias.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<GeographFias> : public ToJsonConverterTemplate<GeographFias>
{
public:
  QJsonObject toJson(const GeographFiasShared& geographFias) const override;
};

} // namespace light


#endif // GEOGRAPHFIASTOJSON_H
