#include "NodeToJson.h"

#include "Node.h"
#include "Contract.h"
#include "Geograph.h"
#include "EquipmentOwner.h"
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
  nodeJson["comments"] = node->getComment();
  nodeJson["price"] = node->getPrice();

  ContractShared contract = node->getContract();
  if(contract) {
    nodeJson["contractId"] = QJsonValue::fromVariant(contract->getId());
    nodeJson["contractCode"] = contract->getCode();
  }

  GeographShared geograph = node->getGeograph();
  if(geograph) {
    nodeJson["geographId"] = QJsonValue::fromVariant(geograph->getId());
    nodeJson["geographCode"] = geograph->getCode();
  }

  ContragentShared owner = node->getOwner();
  if(owner) {
    nodeJson["ownerId"] = QJsonValue::fromVariant(owner->getId());
    nodeJson["ownerCode"] = owner->getCode();
  }

  NodeTypeShared nodeType = node->getNodeType();
  if(nodeType) {
    nodeJson["nodeTypeId"] = QJsonValue::fromVariant(nodeType->getId());
    nodeJson["nodeTypeCode"] = nodeType->getCode();
  }

  return nodeJson;
}

} // namespace light
