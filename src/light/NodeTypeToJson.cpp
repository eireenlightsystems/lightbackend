#include "NodeTypeToJson.h"

#include "NodeType.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

void NodeTypeToJson::convert(const NodeTypeSharedList& nodeTypes) {
  QJsonArray jsonNodeTypes;
  for (const auto& nodeType : nodeTypes) {
    QJsonObject nodeTypeJson;
    nodeTypeJson["id"] = QJsonValue::fromVariant(nodeType->getId());
    nodeTypeJson["code"] = nodeType->getCode();
    jsonNodeTypes << nodeTypeJson;
  }
  setJsonDocument(QJsonDocument(jsonNodeTypes));
}

} // namespace light
