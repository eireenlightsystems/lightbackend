#include "FixtureGroup.h"

#include "FixtureGroupType.h"
#include "Contragent.h"

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

} // namespace light
