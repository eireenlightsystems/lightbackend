#include "NodeToJson.h"

#include "Node.h"
#include "Contract.h"
#include "Geograph.h"
#include "Contragent.h"
#include "EquipmentType.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

void NodeToJson::convert(const NodeSharedList& nodes) {
  QJsonArray jsonNodes;
  for (const auto& n : nodes) {
    QJsonObject node;
    node["nodeId"] = QJsonValue::fromVariant(n->getId());
    node["n_coordinate"] = n->getLatitude();
    node["e_coordinate"] = n->getLongitude();
    node["comments"] = n->getComment();
    node["price"] = n->getPrice();

    ContractShared contract = n->getContract();
    if(contract) {
      node["contractId"] = QJsonValue::fromVariant(contract->getId());
      node["contractCode"] = contract->getCode();
    }

    GeographShared geograph = n->getGeograph();
    if(geograph) {
      node["geographId"] = QJsonValue::fromVariant(geograph->getId());
      node["geographCode"] = geograph->getCode();
    }

    ContragentShared owner = n->getOwner();
    if(owner) {
      node["ownerId"] = QJsonValue::fromVariant(owner->getId());
      node["ownerCode"] = owner->getCode();
    }

    EquipmentTypeShared nodeType;
    if(nodeType) {
      node["nodeTypeId"] = QJsonValue::fromVariant(nodeType->getId());
      node["nodeTypeCode"] = nodeType->getCode();
    }

    jsonNodes << node;
  }

  setJsonDocument(QJsonDocument(jsonNodes));
}

} // namespace light
