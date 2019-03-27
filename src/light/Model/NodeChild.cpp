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

double NodeChild::getLatitude() const {
  if (node) {
    return node->getLatitude();
  }

  return 0.0;
}

double NodeChild::getLongitude() const {
  if (node) {
    return node->getLongitude();
  }

  return 0.0;
}

GeographShared NodeChild::getGeograph() const {
  if (node)
    return node->getGeograph();

  return GeographShared();
}

} // namespace light
