#include "Node.h"

#include "Contract.h"
#include "Contragent.h"
#include "NodeType.h"
#include "Geograph.h"

namespace light {

QGeoCoordinate Node::getCoordinate() const {
  return coordinate;
}

double Node::getLatitude() const {
  return coordinate.latitude();
}

double Node::getLongitude() const {
  return coordinate.longitude();
}

void Node::setCoordinate(const QGeoCoordinate& value) {
  coordinate = value;
}

void Node::setCoordinate(double latitude, double longitude) {
  setCoordinate(QGeoCoordinate(latitude, longitude));
}

NodeTypeShared Node::getNodeType() const {
  return nodeType;
}

ID Node::getNodeTypeId() const {
  if (nodeType)
    return nodeType->getId();

  return 0;
}

void Node::setNodeType(const NodeTypeShared& value) {
  nodeType = value;
}

GeographShared Node::getGeograph() const {
  return geograph;
}

void Node::setGeograph(const GeographShared& value) {
  geograph = value;
}

} // namespace light
