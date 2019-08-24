#include "UserToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>
#include "User.h"

namespace light {

QJsonObject ToJsonConverter<User>::toJson(const UserShared& user) const {
  QJsonObject userJson;
  userJson["userId"] = QJsonValue::fromVariant(user->getId());
  userJson["contragentId"] = QJsonValue::fromVariant(user->getContragentId());
  userJson["login"] = user->getLogin();
  userJson["contragentCode"] = user->getContragentCode();
  userJson["contragentName"] = user->getContragentName();
  userJson["contragentInn"] = user->getContragentInn();
  userJson["contragentAdres"] = user->getContragentAdres();
  userJson["comments"] = user->getComments();

  return userJson;
}

QJsonObject ToJsonConverter<UserInRole>::toJson(const UserInRoleShared& userInRole) const {
  ToJsonConverter<User> userConverter;
  return userConverter.toJson(userInRole.dynamicCast<User>());
}

} // namespace light
