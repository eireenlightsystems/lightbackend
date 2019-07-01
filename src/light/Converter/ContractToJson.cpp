#include "ContractToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Contract>::toJson(const ContractShared& contract) const {
  QJsonObject contractJson;
  contractJson["id"] = QJsonValue::fromVariant(contract->getId());
  contractJson["contractTypeId"] = QJsonValue::fromVariant(contract->getContractTypeId());
  contractJson["senderId"] = QJsonValue::fromVariant(contract->getSenderId());
  contractJson["recipientId"] = QJsonValue::fromVariant(contract->getRecipientId());
  contractJson["contractTypeCode"] = contract->getContractTypeCode();
  contractJson["senderCode"] = contract->getSenderCode();
  contractJson["recipientCode"] = contract->getRecipientCode();
  contractJson["code"] = contract->getCode();
  contractJson["name"] = contract->getName();
  contractJson["comments"] = contract->getComments();

  return contractJson;
}

} // namespace light
