#ifndef GATEWAYCONTRACTTOJSON_H
#define GATEWAYCONTRACTTOJSON_H

#include "ToJsonConverter.h"
#include "Gateway.h"

namespace light {

template <>
class ToJsonConverter<GatewayContract> : public ToJsonConverterTemplate<GatewayContract>
{
public:
  QJsonObject toJson(const GatewayContractShared& gatewayContract) const override;
};

}

#endif // GATEWAYCONTRACTTOJSON_H
