#include "SensorToJson.h"

#include "Contract.h"
#include "EquipmentOwner.h"
#include "Geograph.h"
#include "Node.h"
#include "Sensor.h"
#include "SensorType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Sensor>::toJson(const SensorShared& sensor) const {
  QJsonObject sensorJson;
  sensorJson["id"] = QJsonValue::fromVariant(sensor->getId());
  sensorJson["serialNumber"] = sensor->getSerialNumber();
  sensorJson["comment"] = sensor->getComment();

  auto type = sensor->getType();
  if (type) {
    sensorJson["sensorTypeId"] = QJsonValue::fromVariant(type->getId());
    sensorJson["sensorTypeCode"] = type->getCode();
  }

  ContractShared contract = sensor->getContract();
  if (contract) {
    sensorJson["contractId"] = QJsonValue::fromVariant(contract->getId());
    sensorJson["contractCode"] = contract->getCode();
  }

  ContragentShared owner = sensor->getOwner();
  if (owner) {
    sensorJson["ownerId"] = QJsonValue::fromVariant(owner->getId());
    sensorJson["ownerCode"] = owner->getCode();
  }

  GeographShared geograph = sensor->getGeograph();
  if (geograph) {
    sensorJson["geographId"] = QJsonValue::fromVariant(geograph->getId());
    sensorJson["geographCode"] = geograph->getCode();
  }

  NodeShared node = sensor->getNode();
  if (node) {
    sensorJson["nodeId"] = QJsonValue::fromVariant(node->getId());
    sensorJson["n_coordinate"] = node->getLatitude();
    sensorJson["e_coordinate"] = node->getLongitude();
  }

  return sensorJson;
}

} // namespace light
