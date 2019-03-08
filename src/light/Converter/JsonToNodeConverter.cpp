#include "JsonToNodeConverter.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

namespace light {

template <>
NodeInsertParameters FromJsonConverter<NodeInsertParameters>::parse(const QJsonObject& jsonObject) {
  NodeInsertParameters insertParameters;
  insertParameters.contractId = jsonObject["contractId"].toVariant().value<ID>();
  insertParameters.geographId = jsonObject["geographId"].toVariant().value<ID>();
  insertParameters.nodeTypeId = jsonObject["nodeTypeId"].toVariant().value<ID>();
  double latitude = jsonObject["n_coordinate"].toDouble();
  double longitude = jsonObject["e_coordinate"].toDouble();
  insertParameters.coordinate = QGeoCoordinate(latitude, longitude);
  insertParameters.price = jsonObject["price"].toDouble();
  insertParameters.comment = jsonObject["comment"].toString();
  return insertParameters;
}

template <>
NodeUpdateParameters FromJsonConverter<NodeUpdateParameters>::parse(const QJsonObject& jsonObject) {
  NodeInsertParameters insertParameters = FromJsonConverter<NodeInsertParameters>::parse(jsonObject);
  NodeUpdateParameters updateParameters;
  updateParameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  updateParameters.contractId = insertParameters.contractId;
  updateParameters.geographId = insertParameters.geographId;
  updateParameters.nodeTypeId = insertParameters.nodeTypeId;
  updateParameters.coordinate = insertParameters.coordinate;
  updateParameters.price = insertParameters.price;
  updateParameters.comment = insertParameters.comment;
  return updateParameters;
}

template <>
NodeCoordinateParameters FromJsonConverter<NodeCoordinateParameters>::parse(const QJsonObject& jsonObject) {
  NodeCoordinateParameters parameters;
  parameters.nodeId = jsonObject["nodeId"].toVariant().value<ID>();
  double latitude = jsonObject["n_coordinate"].toDouble();
  double longitude = jsonObject["e_coordinate"].toDouble();
  parameters.coordinate = QGeoCoordinate(latitude, longitude);
  return parameters;
}

} // namespace light
