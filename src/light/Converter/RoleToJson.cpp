#include "RoleToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Role>::toJson(const RoleShared& role) const {
  QJsonObject roleJson;
  roleJson["id"] = QJsonValue::fromVariant(role->getId());
  roleJson["name"] = role->getName();
  roleJson["comments"] = role->getComments();

  return roleJson;
}

} // namespace light
