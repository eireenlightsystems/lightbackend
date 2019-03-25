#include "GatewayToJson.h"

#include "Contract.h"
#include "EquipmentOwner.h"
#include "Gateway.h"
#include "GatewayType.h"
#include "Geograph.h"
#include "Node.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Gateway>::toJson(const GatewayShared& gateway) const {
  QJsonObject gatewayJson;
  gatewayJson["gatewayId"] = QJsonValue::fromVariant(gateway->getId());
  gatewayJson["nodeGroupName"] = gateway->getName();
  gatewayJson["serialNumber"] = gateway->getSerialNumber();
  gatewayJson["comment"] = gateway->getComment();

  ContractShared contract = gateway->getContract();
  if (contract) {
    gatewayJson["contractId"] = QJsonValue::fromVariant(contract->getId());
    gatewayJson["contractCode"] = contract->getCode();
  }

  ContragentShared owner = gateway->getOwner();
  if (owner) {
    gatewayJson["ownerId"] = QJsonValue::fromVariant(owner->getId());
    gatewayJson["ownerCode"] = owner->getCode();
  }

  GatewayTypeShared gatewayType = gateway->getGatewayType();
  if (gatewayType) {
    gatewayJson["gatewayTypeId"] = QJsonValue::fromVariant(gatewayType->getId());
    gatewayJson["gatewayTypeCode"] = gatewayType->getCode();
  }

  GeographShared geograph = gateway->getGeograph();
  if (geograph) {
    gatewayJson["geographId"] = QJsonValue::fromVariant(geograph->getId());
    gatewayJson["geographCode"] = geograph->getCode();
  }

  NodeShared node = gateway->getNode();
  if (node) {
    gatewayJson["n_coordinate"] = node->getLatitude();
    gatewayJson["e_coordinate"] = node->getLongitude();
  }

  return gatewayJson;
}

} // namespace light
