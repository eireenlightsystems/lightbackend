#ifndef GROGRAPHTOJSON_H
#define GROGRAPHTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<Geograph>::toJson(const GeographShared& geograph) const;

} // namespace light

#endif // GROGRAPHTOJSON_H
