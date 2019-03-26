#include "NodeChild.h"

#include "Node.h"

namespace light {

NodeShared NodeChild::getNode() const {
  return node;
}

ID NodeChild::getNodeId() const {
  if (node)
    return node->getId();

  return 0;
}

void NodeChild::setNode(const NodeShared& value) {
  node = value;
}

GeographShared NodeChild::getGeograph() const {
  if (node)
    return node->getGeograph();

  return GeographShared();
}

} // namespace light
