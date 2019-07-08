#include "ContragentToJson.h"

#include "Contragent.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Contragent>::toJson(const ContragentShared& contragent) const {
  QJsonObject contragentJson;
  contragentJson["id"] = QJsonValue::fromVariant(contragent->getId());
  contragentJson["code"] = contragent->getCode();
  contragentJson["name"] = contragent->getName();
  contragentJson["inn"] = contragent->getInn();
  contragentJson["comments"] = contragent->getComments();

  contragentJson["geographId"] = QJsonValue::fromVariant(contragent->getGeographId());
  contragentJson["geographCode"] = contragent->getGeographCode();

  return contragentJson;
}
} // namespace light
