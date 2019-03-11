#include "ContragentToJson.h"

#include "Contragent.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<Contragent>::toJson(const ContragentShared& contragent) const {
  QJsonObject contragentJson;
  contragentJson["id"] = QJsonValue::fromVariant(contragent->getId());
  contragentJson["name"] = contragent->getName();

  return contragentJson;
}
} // namespace light
