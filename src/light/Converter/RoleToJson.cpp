#include "RoleToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Role>::toJson(const RoleShared& role) const {
  QJsonObject roleJson;
  roleJson["roleId"] = QJsonValue::fromVariant(role->getId());
  roleJson["contragentId"] = QJsonValue::fromVariant(role->getContragentId());
  roleJson["contragentCode"] = role->getContragentCode();
  roleJson["contragentName"] = role->getContragentName();
  roleJson["contragentInn"] = role->getContragentInn();
  roleJson["contragentAdres"] = role->getContragentAdres();
  roleJson["name"] = role->getName();
  roleJson["comments"] = role->getComments();

  return roleJson;
}

} // namespace light
