#include "ComponentToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Component>::toJson(const ComponentShared& component) const {
  QJsonObject componentJson;
  componentJson["componentId"] = QJsonValue::fromVariant(component->getId());
  componentJson["code"] = component->getCode();
  componentJson["name"] = component->getName();
  componentJson["comments"] = component->getComments();
  componentJson["rights"] = component->getRights();

  return componentJson;
}

} // namespace light
