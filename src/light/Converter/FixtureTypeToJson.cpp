#include "FixtureTypeToJson.h"

#include "FixtureType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureType>::toJson(const FixtureTypeShared& fixtureType) const {
  QJsonObject fixtureTypeJson;
  fixtureTypeJson["id"] = QJsonValue::fromVariant(fixtureType->getId());
  fixtureTypeJson["code"] = fixtureType->getCode();
  return fixtureTypeJson;
}

} // namespace light
