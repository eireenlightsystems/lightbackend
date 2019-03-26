#ifndef GATEWAY_H
#define GATEWAY_H

#include "Contract.h"
#include "EquipmentType.h"
#include "NodeChild.h"

namespace light {

class GatewayContract : public Contract
{
public:
  GatewayContract() = default;
  explicit GatewayContract(const Contract& other) : Contract(other) {
  }
};

class Gateway : public NodeChild
{
public:
  Gateway() = default;
  ~Gateway() override = default;

  GatewayTypeShared getGatewayType() const;
  ID getGatewayTypeId() const;
  void setGatewayType(const GatewayTypeShared& value);

  QString getName() const;
  void setName(const QString& value);

  NodeSharedList getNodes() const;
  void setNodes(const NodeSharedList& value);
  void addNode(NodeShared node);
  void addNodes(const NodeSharedList& newNodes);
  void removeNode(NodeShared node);
  void removeNode(ID nodeId);

private:
  GatewayTypeShared gatewayType;
  QString name;
  NodeSharedList nodes;
};
} // namespace light

#endif // GATEWAY_H
