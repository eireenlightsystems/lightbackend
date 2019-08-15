#include "UserToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<User>::toJson(const UserShared& user) const {
  QJsonObject userJson;
  userJson["id"] = QJsonValue::fromVariant(user->getId());
  userJson["contragentId"] = QJsonValue::fromVariant(user->getContragentId());
  userJson["login"] = user->getLogin();
  userJson["contragentCode"] = user->getContragentCode();
  userJson["contragentName"] = user->getContragentName();
  userJson["contragentInn"] = user->getContragentInn();
  userJson["contragentAdres"] = user->getContragentAdres();
  userJson["comments"] = user->getComments();

  return userJson;
}

} // namespace light
