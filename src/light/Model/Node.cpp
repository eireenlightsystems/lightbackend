#include "Node.h"

#include "Contract.h"
#include "Contragent.h"
#include "EquipmentType.h"
#include "Geograph.h"

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

ID Node::getOwnerId() const {
  if (owner)
    return owner->getId();

  return 0;
}

void Node::setOwner(const ContragentShared& value) {
  owner = value;
}

EquipmentTypeShared Node::getEquipmentType() const {
  return equipmentType;
}

ID Node::getEquipmentTypeId() const {
  if (equipmentType)
    return equipmentType->getId();

  return 0;
}

void Node::setEquipmentType(const EquipmentTypeShared& value) {
  equipmentType = value;
}

GeographShared Node::getGeograph() const {
  return geograph;
}

ID Node::getGeographId() const {
  if (geograph)
    return geograph->getId();

  return 0;
}

void Node::setGeograph(const GeographShared& value) {
  geograph = value;
}

ContractShared Node::getContract() const {
  return contract;
}

ID Node::getContractId() const {
  if (contract)
    return contract->getId();

  return 0;
}

void Node::setContract(const ContractShared& value) {
  contract = value;
}

} // namespace light
