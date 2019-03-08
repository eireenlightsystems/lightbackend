#include "JsonToGatewayConverter.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

namespace light {

template <>
GatewayInsertParameters FromJsonConverter<GatewayInsertParameters>::parse(const QJsonObject& jsonObject) {
  GatewayInsertParameters insertParameters;
  insertParameters.price = jsonObject["price"].toDouble();
  insertParameters.comment = jsonObject["comment"].toString();
  insertParameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  insertParameters.contractId = jsonObject["contractId"].toVariant().value<ID>();
  insertParameters.gatewayTypeId = jsonObject["gatewayTypeId"].toVariant().value<ID>();
  return insertParameters;
}

template <>
GatewayUpdateParameters FromJsonConverter<GatewayUpdateParameters>::parse(const QJsonObject& jsonObject) {
  auto insertParameters = FromJsonConverter<GatewayInsertParameters>::parse(jsonObject);
  GatewayUpdateParameters updateParameters;
  updateParameters.gatewayId = jsonObject["gatewayId"].toVariant().value<ID>();
  updateParameters.price = insertParameters.price;
  updateParameters.comment = insertParameters.comment;
  updateParameters.nodeId = insertParameters.nodeId;
  updateParameters.contractId = insertParameters.contractId;
  updateParameters.gatewayTypeId = insertParameters.gatewayTypeId;
  return updateParameters;
}

} // namespace light
