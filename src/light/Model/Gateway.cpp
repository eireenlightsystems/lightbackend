#include "Gateway.h"

#include "GatewayType.h"
#include "Node.h"

namespace light {

GatewayTypeShared Gateway::getGatewayType() const {
  return gatewayType;
}

ID Gateway::getGatewayTypeId() const {
  if (gatewayType)
    return gatewayType->getId();

  return 0;
}

void Gateway::setGatewayType(const GatewayTypeShared& value) {
  gatewayType = value;
}

NodeShared Gateway::getNode() const {
  return node;
}

ID Gateway::getNodeId() const {
  if (node)
    return node->getId();

  return 0;
}

void Gateway::setNode(const NodeShared& value) {
  node = value;
}

GeographShared Gateway::getGeograph() const {
  if (node)
    return node->getGeograph();

  return GeographShared();
}

QString Gateway::getName() const {
  return name;
}

void Gateway::setName(const QString& value) {
  name = value;
}

} // namespace light
