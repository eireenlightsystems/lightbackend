#ifndef GATEWAYTYPETOJSON_H
#define GATEWAYTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<GatewayType>::toJson(const GatewayTypeShared& gatewayType) const;

}

#endif // GATEWAYTYPETOJSON_H
