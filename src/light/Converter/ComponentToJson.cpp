#include "ComponentToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Component>::toJson(const ComponentShared& component) const {
  QJsonObject componentJson;
  componentJson["id"] = QJsonValue::fromVariant(component->getId());
  componentJson["name"] = component->getName();
  componentJson["comments"] = component->getComments();

  return componentJson;
}

} // namespace light
