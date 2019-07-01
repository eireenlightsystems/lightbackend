#include "ContractTypeToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<ContractType>::toJson(const ContractTypeShared& contractType) const {
  QJsonObject contractJson;
  contractJson["id"] = QJsonValue::fromVariant(contractType->getId());
  contractJson["code"] = contractType->getCode();
  contractJson["name"] = contractType->getName();
  contractJson["comments"] = contractType->getComments();

  return contractJson;
}

} // namespace light
