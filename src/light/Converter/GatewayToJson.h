#ifndef GATEWAYTOJSON_H
#define GATEWAYTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<Gateway>::toJson(const GatewayShared& gateway) const;

} // namespace light

#endif // GATEWAYTOJSON_H
