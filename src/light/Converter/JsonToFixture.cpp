#include "JsonToFixture.h"

#include <QJsonObject>
#include <QVariant>

namespace light {
/*
template <>
FixtureInsertParameters FromJsonConverter<FixtureInsertParameters>::parse(const QJsonObject& jsonObject) {
  FixtureInsertParameters insertParameters;
  insertParameters.contractId = jsonObject["contractId"].toVariant().value<ID>();
  insertParameters.installerId = jsonObject["installerId"].toVariant().value<ID>();
  insertParameters.heightTypeId = jsonObject["heightTypeId"].toVariant().value<ID>();
  insertParameters.substationId = jsonObject["substationId"].toVariant().value<ID>();
  insertParameters.fixtureTypeId = jsonObject["fixtureTypeId"].toVariant().value<ID>();
  insertParameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  insertParameters.price = jsonObject["price"].toDouble();
  insertParameters.comment = jsonObject["comment"].toString();
  return insertParameters;
}

template <>
FixtureUpdateParameters FromJsonConverter<FixtureUpdateParameters>::parse(const QJsonObject& jsonObject) {
  const auto insertParameters = FromJsonConverter<FixtureInsertParameters>::parse(jsonObject);
  FixtureUpdateParameters updateParameters;
  updateParameters.fixtureId = jsonObject["fixtureId"].toVariant().value<ID>();
  updateParameters.contractId = insertParameters.contractId;
  updateParameters.installerId = insertParameters.installerId;
  updateParameters.heightTypeId = insertParameters.heightTypeId;
  updateParameters.substationId = insertParameters.substationId;
  updateParameters.fixtureTypeId = insertParameters.fixtureTypeId;
  updateParameters.nodeId = insertParameters.nodeId;
  updateParameters.price = insertParameters.price;
  updateParameters.comment = insertParameters.comment;

  return updateParameters;
}
*/
} // namespace light
