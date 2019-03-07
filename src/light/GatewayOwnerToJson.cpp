#include "GatewayOwnerToJson.h"

#include "EquipmentOwner.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

void GatewayOwnerToJson::convert(const EquipmentOwnerSharedList &equipmentOwners) {
  QJsonArray jsonOwners;
  for (const auto& gatewayOwner : equipmentOwners) {
    QJsonObject ownerJson;
    ownerJson["id"] = QJsonValue::fromVariant(gatewayOwner->getId());
    ownerJson["name"] = gatewayOwner->getName();

    jsonOwners << ownerJson;
  }
  setJsonDocument(QJsonDocument(jsonOwners));
}

} // namespace light
