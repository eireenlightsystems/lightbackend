#include "GatewayTypeToJson.h"

#include "GatewayType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<GatewayType>::toJson(const GatewayTypeShared& gatewayType) const {
  QJsonObject gatewayTypeJson;
  gatewayTypeJson["id"] = QJsonValue::fromVariant(gatewayType->getId());
  gatewayTypeJson["code"] = gatewayType->getCode();
  gatewayTypeJson["name"] = gatewayType->getName();
  gatewayTypeJson["model"] = gatewayType->getModel();
  gatewayTypeJson["comments"] = gatewayType->getComment();
  gatewayTypeJson["communicationStandard"] = gatewayType->getCommunicationStandard();
  return gatewayTypeJson;
}

} // namespace light
