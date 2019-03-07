#include "Equipment.h"

#include "Contract.h"
#include "EquipmentOwner.h"
#include "Geograph.h"

namespace light {

ID Equipment::getId() const {
  return id;
}

void Equipment::setId(const ID& value) {
  id = value;
}

double Equipment::getPrice() const {
  return price;
}

void Equipment::setPrice(double value) {
  price = value;
}

QString Equipment::getComment() const {
  return comment;
}

void Equipment::setComment(const QString& value) {
  comment = value;
}

ContractShared Equipment::getContract() const {
  return contract;
}

ID Equipment::getContractId() const {
  if (contract)
    return contract->getId();

  return 0;
}

void Equipment::setContract(const ContractShared& value) {
  contract = value;
}

EquipmentOwnerShared Equipment::getOwner() const {
  return owner;
}

ID Equipment::getOwnerId() const {
  if (owner)
    return owner->getId();

  return 0;
}

void Equipment::setOwner(const EquipmentOwnerShared& value) {
  owner = value;
}

ID Equipment::getGeographId() const {
  auto geograph = getGeograph();
  if (geograph)
    return geograph->getId();

  return 0;
}

} // namespace light
