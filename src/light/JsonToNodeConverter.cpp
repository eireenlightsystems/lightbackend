#include "JsonToNodeConverter.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

namespace light {

void JsonInsertParametersToNodeConverter::convert(const QByteArray& data) {
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

QList<NodeSaveParameters> JsonInsertParametersToNodeConverter::getParameters() const {
  return parameters;
}

NodeSaveParameters JsonInsertParametersToNodeConverter::parse(const QJsonObject& jsonObject) {
  NodeSaveParameters parameters;
  parameters.nodeId = 0;
  parameters.contractId = jsonObject["contractId"].toVariant().value<ID>();
  parameters.geographId = jsonObject["geographId"].toVariant().value<ID>();
  parameters.nodeTypeId = jsonObject["nodeTypeId"].toVariant().value<ID>();
  double latitude = jsonObject["n_coordinate"].toDouble();
  double longitude = jsonObject["e_coordinate"].toDouble();
  parameters.coordinate = QGeoCoordinate(latitude, longitude);
  parameters.price = jsonObject["price"].toDouble();
  parameters.comment = jsonObject["comment"].toString();
  return parameters;
}

NodeSaveParameters JsonUpdateParametersToNodeConverter::parse(const QJsonObject& jsonObject) {
  NodeSaveParameters parameters = JsonInsertParametersToNodeConverter::parse(jsonObject);
  parameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  return parameters;
}

void JsonNodeCoordinatesConverter::convert(const QByteArray& data) {
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

QList<NodeCoordinateParameters> JsonNodeCoordinatesConverter::getParameters() const {
  return parameters;
}

NodeCoordinateParameters JsonNodeCoordinatesConverter::parse(const QJsonObject& jsonObject) {
  NodeCoordinateParameters parameters;
  parameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  double latitude = jsonObject["n_coordinate"].toDouble();
  double longitude = jsonObject["e_coordinate"].toDouble();
  parameters.coordinate = QGeoCoordinate(latitude, longitude);
  return parameters;
}

} // namespace light
