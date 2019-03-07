#include "GatewayTypeToJson.h"

#include "GatewayType.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

void GatewayTypeToJson::convert(const GatewayTypeSharedList& gatewayTypes) {
  QJsonArray jsonGatewayTypes;
  for (const auto& gatewayType : gatewayTypes) {
    QJsonObject gatewayTypeJson;
    gatewayTypeJson["id"] = QJsonValue::fromVariant(gatewayType->getId());
    gatewayTypeJson["code"] = gatewayType->getCode();
    jsonGatewayTypes << gatewayTypeJson;
  }
  setJsonDocument(QJsonDocument(jsonGatewayTypes));
}

} // namespace light
