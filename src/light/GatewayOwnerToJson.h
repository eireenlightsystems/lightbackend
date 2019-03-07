#ifndef GATEWAYOWNERTOJSON_H
#define GATEWAYOWNERTOJSON_H

#include "BaseJsonConverter.h"
#include "typedefs.h"

namespace light {
class GatewayOwnerToJson : public BaseJsonConverter
{
public:
  GatewayOwnerToJson() = default;
  ~GatewayOwnerToJson() override = default;
  void convert(const EquipmentOwnerSharedList &equipmentOwners);
};
}

#endif // GATEWAYOWNERTOJSON_H
