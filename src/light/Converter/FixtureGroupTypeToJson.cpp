#include "FixtureGroupTypeToJson.h"

#include "FixtureGroupType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<FixtureGroupType>::toJson(const FixtureGroupTypeShared& fixtureGroupType) const {
  QJsonObject fixtureGroupTypeJson;
  fixtureGroupTypeJson["id"] = QJsonValue::fromVariant(fixtureGroupType->getId());
  fixtureGroupTypeJson["name"] = fixtureGroupType->getName();
  return fixtureGroupTypeJson;
}

}
