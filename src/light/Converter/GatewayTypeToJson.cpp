#include "GatewayTypeToJson.h"

#include "GatewayType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<GatewayType>::toJson(const GatewayTypeShared& gatewayType) const {
  QJsonObject gatewayTypeJson;
  gatewayTypeJson["id"] = QJsonValue::fromVariant(gatewayType->getId());
  gatewayTypeJson["code"] = gatewayType->getCode();
  return gatewayTypeJson;
}

} // namespace light
