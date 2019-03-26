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
  return sensorTypeJson;
}

} // namespace light
