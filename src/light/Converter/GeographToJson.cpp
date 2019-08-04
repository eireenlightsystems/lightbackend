#include "GeographToJson.h"

#include "Geograph.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Geograph>::toJson(const GeographShared& geograph) const {
  QJsonObject geographJson;
  geographJson["id"] = QJsonValue::fromVariant(geograph->getId());
  geographJson["code"] = geograph->getCode();
  geographJson["name"] = geograph->getName();
  geographJson["fullName"] = geograph->getFullName();
  return geographJson;
}

} // namespace light
