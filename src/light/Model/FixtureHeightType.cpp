#include "FixtureHeightType.h"

namespace light {

QString FixtureHeightType::getCode() const {
  return code;
}

void FixtureHeightType::setCode(const QString& value) {
  code = value;
}

QString FixtureHeightType::getName() const {
  return name;
}

void FixtureHeightType::setName(const QString& value) {
  name = value;
}

ID FixtureHeightType::getId() const
{
  return id;
}

void FixtureHeightType::setId(const ID &value)
{
  id = value;
}
} // namespace light
