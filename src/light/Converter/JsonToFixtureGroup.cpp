#include "JsonToFixtureGroup.h"

#include <QJsonObject>
#include <QVariant>

namespace light {
/*
template<>
FixtureGroupInsertParameters FromJsonConverter<FixtureGroupInsertParameters>::parse(const QJsonObject& jsonObject) {
  FixtureGroupInsertParameters insertParameters;
  insertParameters.ownerId = jsonObject["ownerId"].toVariant().value<ID>();
  insertParameters.groupTypeId = jsonObject["fixtureGroupTypeId"].toVariant().value<ID>();
  insertParameters.name = jsonObject["fixtureGroupName"].toString();
  return insertParameters;
}

template<>
FixtureGroupUpdateParameters FromJsonConverter<FixtureGroupUpdateParameters>::parse(const QJsonObject& jsonObject) {
  auto insertParameters = FromJsonConverter<FixtureGroupInsertParameters>::parse(jsonObject);
  FixtureGroupUpdateParameters updateParameters;
  updateParameters.groupId = jsonObject["fixtureGroupId"].toVariant().value<ID>();
  updateParameters.ownerId = insertParameters.ownerId;
  updateParameters.groupTypeId = insertParameters.groupTypeId;
  updateParameters.name = insertParameters.name;

  return updateParameters;
}
*/
} // namespace light
