#include "JsonToGatewayConverter.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

namespace light {

void JsonInsertParametersToGatewayConverter::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid())
    return;

  if (jDoc.isArray()) {
    auto paramsArray = jDoc.array();
    for (const auto jsonValue : paramsArray) {
      auto jsonObject = jsonValue.toObject();
      parameters << parse(jsonObject);
    }
  } else {
    auto jsonObject = jDoc.object();
    parameters << parse(jsonObject);
  }
}

GatewaySaveParameters JsonInsertParametersToGatewayConverter::parse(const QJsonObject& jsonObject) {
  GatewaySaveParameters saveParameters;

  saveParameters.gatewayId = 0;
  saveParameters.price = jsonObject["price"].toDouble();
  saveParameters.comment = jsonObject["comment"].toString();
  saveParameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  saveParameters.contractId = jsonObject["contractId"].toVariant().value<ID>();
  saveParameters.gatewayTypeId = jsonObject["gatewayTypeId"].toVariant().value<ID>();

  return saveParameters;
}

QList<GatewaySaveParameters> JsonInsertParametersToGatewayConverter::getParameters() const {
  return parameters;
}

void JsonUpdateParametersToGatewayConverter::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid())
    return;

  if (jDoc.isArray()) {
    auto paramsArray = jDoc.array();
    for (const auto jsonValue : paramsArray) {
      auto jsonObject = jsonValue.toObject();
      parameters << parse(jsonObject);
    }
  } else {
    auto jsonObject = jDoc.object();
    parameters << parse(jsonObject);
  }
}

GatewaySaveParameters JsonUpdateParametersToGatewayConverter::parse(const QJsonObject& jsonObject) {
  GatewaySaveParameters saveParameters;

  saveParameters.gatewayId = jsonObject["gatewayId"].toVariant().value<ID>();
  saveParameters.price = jsonObject["price"].toDouble();
  saveParameters.comment = jsonObject["comment"].toString();
  saveParameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  saveParameters.contractId = jsonObject["contractId"].toVariant().value<ID>();
  saveParameters.gatewayTypeId = jsonObject["gatewayTypeId"].toVariant().value<ID>();

  return saveParameters;
}

QList<GatewaySaveParameters> JsonUpdateParametersToGatewayConverter::getParameters() const {
  return parameters;
}

} // namespace light
