#include "Node.h"

namespace light {

ID Node::getId() const {
  return id;
}

void Node::setId(const ID& value) {
  id = value;
}

QGeoCoordinate Node::getCoordinate() const {
  return coordinate;
}

void Node::setCoordinate(const QGeoCoordinate& value) {
  coordinate = value;
}

void Node::setCoordinate(double latitude, double longitude) {
  setCoordinate(QGeoCoordinate(latitude, longitude));
}

double Node::getPrice() const {
  return price;
}

void Node::setPrice(double value) {
  price = value;
}

QString Node::getComment() const {
  return comment;
}

void Node::setComment(const QString& value) {
  comment = value;
}

ContragentShared Node::getOwner() const {
  return owner;
}

void Node::setOwner(const ContragentShared& value) {
  owner = value;
}

EquipmentTypeShared Node::getEquipmentType() const {
  return equipmentType;
}

void Node::setEquipmentType(const EquipmentTypeShared& value) {
  equipmentType = value;
}

GeographShared Node::getGeograph() const {
  return geograph;
}

void Node::setGeograph(const GeographShared& value) {
  geograph = value;
}

ContractShared Node::getContract() const {
  return contract;
}

void Node::setContract(const ContractShared& value) {
  contract = value;
}

} // namespace light
