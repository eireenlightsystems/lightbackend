#include "FixtureGroupToJson.h"

#include "Contragent.h"
#include "FixtureGroup.h"
#include "FixtureGroupType.h"
#include "Geograph.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<FixtureGroup>::toJson(const FixtureGroupShared& fixtureGroup) const {
  QJsonObject fixtureGroupJson;
  fixtureGroupJson["fixtureGroupId"] = QJsonValue::fromVariant(fixtureGroup->getId());
  fixtureGroupJson["fixtureGroupName"] = fixtureGroup->getName();
  fixtureGroupJson["n_coordinate"] = fixtureGroup->getLatitude();
  fixtureGroupJson["e_coordinate"] = fixtureGroup->getLongitude();

  auto groupType = fixtureGroup->getType();
  if (groupType) {
    fixtureGroupJson["fixtureGroupTypeId"] = QJsonValue::fromVariant(groupType->getId());
    fixtureGroupJson["fixtureGroupTypeName"] = groupType->getName();
  }

  auto owner = fixtureGroup->getOwner();
  if (owner) {
    fixtureGroupJson["ownerId"] = QJsonValue::fromVariant(owner->getId());
    fixtureGroupJson["ownerCode"] = owner->getCode();
  }

  auto geograph = fixtureGroup->getGeograph();
  if (geograph) {
    fixtureGroupJson["geographId"] = QJsonValue::fromVariant(geograph->getId());
    fixtureGroupJson["geographCode"] = geograph->getCode();
  }

  return fixtureGroupJson;
}

} // namespace light
