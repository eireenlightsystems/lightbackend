#include "ContractToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Contract>::toJson(const ContractShared& contract) const {
  QJsonObject contractJson;
  contractJson["id"] = QJsonValue::fromVariant(contract->getId());
  contractJson["code"] = contract->getCode();
  contractJson["name"] = contract->getName();

  return contractJson;
}

} // namespace light
