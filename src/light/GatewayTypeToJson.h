#ifndef GATEWAYTYPETOJSON_H
#define GATEWAYTYPETOJSON_H

#include "BaseJsonConverter.h"

namespace light {

class GatewayTypeToJson : public BaseJsonConverter
{
public:
GatewayTypeToJson() = default;
~GatewayTypeToJson() override = default;
void convert(const GatewayTypeSharedList& gatewayTypes);
};

}

#endif // GATEWAYTYPETOJSON_H
