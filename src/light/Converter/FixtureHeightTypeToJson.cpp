#include "FixtureHeightTypeToJson.h"

#include "FixtureHeightType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureHeightType>::toJson(const FixtureHeightTypeShared& fixtureHeightType) const {
  QJsonObject fixtureTypeJson;
  fixtureTypeJson["id"] = QJsonValue::fromVariant(fixtureHeightType->getId());
  fixtureTypeJson["code"] = fixtureHeightType->getCode();
  fixtureTypeJson["name"] = fixtureHeightType->getName();
  return fixtureTypeJson;
}
} // namespace light
