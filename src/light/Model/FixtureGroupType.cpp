#include "FixtureGroupType.h"

namespace light {

ID FixtureGroupType::getId() const {
  return id;
}

void FixtureGroupType::setId(const ID& value) {
  id = value;
}

QString FixtureGroupType::getName() const {
  return name;
}

void FixtureGroupType::setName(const QString& value) {
  name = value;
}

} // namespace light
