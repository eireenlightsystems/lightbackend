#include "RolerightToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Roleright>::toJson(const RolerightShared& roleright) const {
  QJsonObject rolerightJson;
  rolerightJson["rolerightId"] = QJsonValue::fromVariant(roleright->getId());
  rolerightJson["componentId"] = QJsonValue::fromVariant(roleright->getComponentId());
  rolerightJson["componentCode"] = roleright->getComponentCode();
  rolerightJson["componentName"] = roleright->getComponentName();
  rolerightJson["componentComments"] = roleright->getComponentComments();
  rolerightJson["roleId"] = QJsonValue::fromVariant(roleright->getRoleId());
  rolerightJson["roleName"] = roleright->getRoleName();
  rolerightJson["rights"] = roleright->getRights();
  return rolerightJson;
}

} // namespace light
