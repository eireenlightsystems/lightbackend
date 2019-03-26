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

QString Gateway::getName() const {
  return name;
}

void Gateway::setName(const QString& value) {
  name = value;
}

NodeSharedList Gateway::getNodes() const {
  return nodes;
}

void Gateway::setNodes(const NodeSharedList& value) {
  nodes = value;
}

void Gateway::addNode(NodeShared node) {
  nodes << node;
}

void Gateway::addNodes(const NodeSharedList& newNodes) {
  nodes << newNodes;
}

void Gateway::removeNode(NodeShared node) {
  nodes.removeAll(node);
}

void Gateway::removeNode(ID nodeId) {
  auto it =
      std::remove_if(nodes.begin(), nodes.end(), [nodeId](const NodeShared& node) { return node->getId() == nodeId; });
  if (it != nodes.end()) {
    nodes.erase(it);
  }
}

} // namespace light
