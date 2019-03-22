#ifndef GATEWAYTOJSON_H
#define GATEWAYTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Gateway> : public ToJsonConverterTemplate<Gateway>
{
public:
  QJsonObject toJson(const GatewayShared& contragent) const override;
};

} // namespace light

#endif // GATEWAYTOJSON_H
