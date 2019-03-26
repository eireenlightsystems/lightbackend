#include "Node.h"

#include "Contract.h"
#include "Contragent.h"
#include "Fixture.h"
#include "Gateway.h"
#include "Geograph.h"
#include "NodeType.h"
#include "Sensor.h"
#include "helpers.h"

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

FixtureSharedList Node::getFixtures() const {
  return fixtures;
}

void Node::setFixtures(const FixtureSharedList& value) {
  fixtures = value;
}

void Node::addFixtures(const FixtureSharedList& value) {
  fixtures << value;
}

void Node::removeFixtures(const IDList& ids) {
  helpers::removeByIds(fixtures, ids);
}

GatewaySharedList Node::getGateways() const {
  return gateways;
}

void Node::setGateways(const GatewaySharedList& value) {
  gateways = value;
}

void Node::addGateways(const GatewaySharedList& value) {
  gateways << value;
}

void Node::removeGateways(const IDList& ids) {
  helpers::removeByIds(gateways, ids);
}

SensorSharedList Node::getSensors() const {
  return sensors;
}

void Node::setSensors(const SensorSharedList& value) {
  sensors = value;
}

void Node::addSensors(const SensorSharedList& value) {
  sensors << value;
}

void Node::removeSensors(const IDList& ids) {
  helpers::removeByIds(sensors, ids);
}

} // namespace light
