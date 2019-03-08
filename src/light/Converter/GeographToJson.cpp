#include "GeographToJson.h"

#include "Geograph.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<Geograph>::toJson(const GeographShared& geograph) const {
  QJsonObject geographJson;
  geographJson["id"] = QJsonValue::fromVariant(geograph->getId());
  geographJson["code"] = geograph->getCode();
  geographJson["fullName"] = geograph->getFullName();
  return geographJson;
}

} // namespace light
