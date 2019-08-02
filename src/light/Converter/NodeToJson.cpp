#include "NodeToJson.h"

#include "ContractToJson.h"
#include "ContragentToJson.h"
#include "EquipmentOwner.h"
#include "Geograph.h"
#include "Node.h"
#include "NodeType.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Node>::toJson(const NodeShared& node) const {
  QJsonObject nodeJson;
  nodeJson["nodeId"] = QJsonValue::fromVariant(node->getId());
  nodeJson["n_coordinate"] = node->getLatitude();
  nodeJson["e_coordinate"] = node->getLongitude();
  nodeJson["comment"] = node->getComment();
  nodeJson["numberInGroup"] = node->getNumberInGroup();
  nodeJson["serialNumber"] = node->getSerialNumber();

  ContractShared contract = node->getContract();
  if (contract) {
    nodeJson["contractId"] = QJsonValue::fromVariant(contract->getId());
    nodeJson["contractCode"] = contract->getCode();
  }

  GeographShared geograph = node->getGeograph();
  if (geograph) {
    nodeJson["geographId"] = QJsonValue::fromVariant(node->getGeographId());
    nodeJson["geographFullName"] = node->getGeographFullName();
  }

  ContragentShared owner = node->getOwner();
  if (owner) {
    nodeJson["ownerId"] = QJsonValue::fromVariant(owner->getId());
    nodeJson["ownerCode"] = owner->getCode();
  }

  NodeTypeShared nodeType = node->getNodeType();
  if (nodeType) {
    nodeJson["nodeTypeId"] = QJsonValue::fromVariant(nodeType->getId());
    nodeJson["nodeTypeCode"] = nodeType->getCode();
  }

  return nodeJson;
}

QJsonObject ToJsonConverter<NodeContract>::toJson(const NodeContractShared& nodeContract) const {
  ToJsonConverter<Contract> contractConverter;
  return contractConverter.toJson(nodeContract.dynamicCast<Contract>());
}

QJsonObject ToJsonConverter<NodeOwner>::toJson(const NodeOwnerShared& nodeOwner) const {
  ToJsonConverter<Contragent> contragentConverter;
  return contragentConverter.toJson(nodeOwner.dynamicCast<Contragent>());
}

} // namespace light
