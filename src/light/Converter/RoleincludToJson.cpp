#include "RoleincludToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Roleinclud>::toJson(const RoleincludShared& roleinclud) const {
  QJsonObject roleincludJson;
  roleincludJson["roleincludId"] = QJsonValue::fromVariant(roleinclud->getId());
  roleincludJson["roleId"] = QJsonValue::fromVariant(roleinclud->getRoleId());
  roleincludJson["userId"] = QJsonValue::fromVariant(roleinclud->getUserId());
  return roleincludJson;
}

} // namespace light
