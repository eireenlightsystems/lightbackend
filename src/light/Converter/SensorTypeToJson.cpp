#include "SensorTypeToJson.h"

#include "SensorType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<SensorType>::toJson(const SensorTypeShared& sensorType) const {
  QJsonObject sensorTypeJson;
  sensorTypeJson["id"] = QJsonValue::fromVariant(sensorType->getId());
  sensorTypeJson["code"] = sensorType->getCode();
  sensorTypeJson["name"] = sensorType->getName();
  sensorTypeJson["model"] = sensorType->getModel();
  sensorTypeJson["comments"] = sensorType->getComment();
  sensorTypeJson["detectionRange"] = sensorType->getDetectionRange();
  return sensorTypeJson;
}

} // namespace light
