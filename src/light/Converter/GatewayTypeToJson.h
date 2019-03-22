#ifndef GATEWAYTYPETOJSON_H
#define GATEWAYTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<GatewayType> : public ToJsonConverterTemplate<GatewayType>
{
public:
  QJsonObject toJson(const GatewayTypeShared& contragent) const override;
};

}

#endif // GATEWAYTYPETOJSON_H
