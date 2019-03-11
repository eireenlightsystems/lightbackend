#include "FixtureGroup.h"

#include "Contragent.h"
#include "FixtureGroupType.h"

namespace light {

ID FixtureGroup::getId() const {
  return id;
}

void FixtureGroup::setId(const ID& value) {
  id = value;
}

QString FixtureGroup::getName() const {
  return name;
}

void FixtureGroup::setName(const QString& value) {
  name = value;
}

ContragentShared FixtureGroup::getOwner() const {
  return owner;
}

ID FixtureGroup::getOwnerId() const {
  if (owner) {
    return owner->getId();
  }

  return 0;
}

void FixtureGroup::setOwner(const ContragentShared& value) {
  owner = value;
}

GeographShared FixtureGroup::getGeograph() const {
  return geograph;
}

void FixtureGroup::setGeograph(const GeographShared& value) {
  geograph = value;
}

FixtureGroupTypeShared FixtureGroup::getType() const {
  return type;
}

ID FixtureGroup::getTypeId() const {
  if (type) {
    return type->getId();
  }

  return 0;
}

void FixtureGroup::setType(const FixtureGroupTypeShared& value) {
  type = value;
}

QGeoCoordinate FixtureGroup::getCoordinate() const {
  return coordinate;
}

double FixtureGroup::getLatitude() const {
  return coordinate.latitude();
}

double FixtureGroup::getLongitude() const {
  return coordinate.longitude();
}

void FixtureGroup::setCoordinate(const QGeoCoordinate& value) {
  coordinate = value;
}

void FixtureGroup::setCoordinate(double latitude, double longitude) {
  coordinate = QGeoCoordinate(latitude, longitude);
}

} // namespace light
