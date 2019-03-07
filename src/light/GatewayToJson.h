#ifndef GATEWAYTOJSON_H
#define GATEWAYTOJSON_H

#include "BaseJsonConverter.h"

namespace light {

class GatewayToJson : public BaseJsonConverter
{
public:
  GatewayToJson() = default;
  ~GatewayToJson() override = default;
  void convert(const GatewaySharedList & gateways);
};

} // namespace light

#endif // GATEWAYTOJSON_H
