#include "Fixture.h"

#include "Contract.h"
#include "Contragent.h"
#include "FixtureHeightType.h"
#include "FixtureType.h"
#include "Node.h"
#include "Substation.h"

namespace light {
bool Fixture::getHasGatewayLink() const {
  return hasGatewayLink;
}

void Fixture::setHasGatewayLink(bool value) {
  hasGatewayLink = value;
}

ID Fixture::getId() const {
  return id;
}

void Fixture::setId(const ID& value) {
  id = value;
}

quint8 Fixture::getStandbyLevel() const {
  return standbyLevel;
}

void Fixture::setStandbyLevel(const quint8& value) {
  standbyLevel = value;
}

quint8 Fixture::getWorkLevel() const {
  return workLevel;
}

void Fixture::setWorkLevel(const quint8& value) {
  workLevel = value;
}

quint8 Fixture::getSpeedUp() const {
  return speedUp;
}

void Fixture::setSpeedUp(const quint8& value) {
  speedUp = value;
}

quint8 Fixture::getSpeedDown() const {
  return speedDown;
}

void Fixture::setSpeedDown(const quint8& value) {
  speedDown = value;
}

ContractShared Fixture::getContract() const {
  return contract;
}

ID Fixture::getContractId() const {
  if (contract) {
    return contract->getId();
  }

  return 0;
}

void Fixture::setContract(const ContractShared& value) {
  contract = value;
}

SubstationShared Fixture::getSubstation() const {
  return substation;
}

ID Fixture::getSubstationId() const {
  if (substation) {
    return substation->getId();
  }

  return 0;
}

void Fixture::setSubstation(const SubstationShared& value) {
  substation = value;
}

ContragentShared Fixture::getInstaller() const {
  return installer;
}

ID Fixture::getInstallerId() const {
  if (installer) {
    return installer->getId();
  }

  return 0;
}

void Fixture::setInstaller(const ContragentShared& value) {
  installer = value;
}

FixtureHeightTypeShared Fixture::getHeightType() const {
  return heightType;
}

ID Fixture::getHeightTypeId() const {
  if (heightType) {
    return heightType->getId();
  }

  return 0;
}

void Fixture::setHeightType(const FixtureHeightTypeShared& value) {
  heightType = value;
}

NodeShared Fixture::getNode() const {
  return node;
}

ID Fixture::getNodeId() const {
  if (node) {
    return node->getId();
  }

  return 0;
}

void Fixture::setNode(const NodeShared& value) {
  node = value;
}

double Fixture::getLatitude() const {
  if (node) {
    return node->getLatitude();
  }

  return 0.0;
}

double Fixture::getLongitude() const {
  if (node) {
    return node->getLongitude();
  }

  return 0.0;
}

GeographShared Fixture::getGeograph() const {
  if (node) {
    return node->getGeograph();
  }

  return GeographShared();
}

ID Fixture::getGeographId() const {
  if (node) {
    return node->getGeographId();
  }
  return 0;
}

FixtureTypeShared Fixture::getType() const {
  return type;
}

ID Fixture::getTypeId() const {
  if (type) {
    return type->getId();
  }
  return 0;
}

void Fixture::setType(const FixtureTypeShared& value) {
  type = value;
}

ContragentShared Fixture::getOwner() const {
  return owner;
}

void Fixture::setOwner(const ContragentShared& value) {
  owner = value;
}

QString Fixture::getComment() const {
  return comment;
}

void Fixture::setComment(const QString& value) {
  comment = value;
}

double Fixture::getPrice() const {
  return price;
}

void Fixture::setPrice(double value) {
  price = value;
}
} // namespace light
