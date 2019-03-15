#include "NodeTypeToJson.h"

#include "NodeType.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<NodeType>::toJson(const NodeTypeShared& nodeType) const {
  QJsonObject nodeTypeJson;
  nodeTypeJson["id"] = QJsonValue::fromVariant(nodeType->getId());
  nodeTypeJson["code"] = nodeType->getCode();
  return nodeTypeJson;
}

} // namespace light