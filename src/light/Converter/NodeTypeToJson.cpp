#include "NodeTypeToJson.h"

#include "NodeType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<NodeType>::toJson(const NodeTypeShared& nodeType) const {
  QJsonObject nodeTypeJson;
  nodeTypeJson["id"] = QJsonValue::fromVariant(nodeType->getId());
  nodeTypeJson["code"] = nodeType->getCode();
  nodeTypeJson["name"] = nodeType->getName();
  nodeTypeJson["model"] = nodeType->getModel();
  nodeTypeJson["comments"] = nodeType->getComment();
  nodeTypeJson["height"] = nodeType->getHeight();
  return nodeTypeJson;
}

} // namespace light
