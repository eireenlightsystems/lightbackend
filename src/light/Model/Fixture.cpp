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

QString Fixture::getComment() const {
  return comment;
}

void Fixture::setComment(const QString& value) {
  comment = value;
}

bool Fixture::isLight() const {
  return workLevel > 0;
}

} // namespace light
