#include "GatewayOwnerToJson.h"

#include "EquipmentOwner.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<EquipmentOwner>::toJson(const EquipmentOwnerShared& equipmentOwner) const {
  QJsonObject ownerJson;
  ownerJson["id"] = QJsonValue::fromVariant(equipmentOwner->getId());
  ownerJson["name"] = equipmentOwner->getName();

  return ownerJson;
}

} // namespace light
