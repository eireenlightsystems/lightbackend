#ifndef GATEWAY_H
#define GATEWAY_H

#include "Equipment.h"
#include "EquipmentType.h"

namespace light {
class Gateway : public Equipment
{
public:
  Gateway() = default;
  ~Gateway() override = default;

  GatewayTypeShared getGatewayType() const;
  ID getGatewayTypeId() const;
  void setGatewayType(const GatewayTypeShared& value);

  NodeShared getNode() const;
  ID getNodeId() const;
  void setNode(const NodeShared& value);

  GeographShared getGeograph() const override;

private:
  GatewayTypeShared gatewayType;
  NodeShared node;
};
} // namespace light

#endif // GATEWAY_H
