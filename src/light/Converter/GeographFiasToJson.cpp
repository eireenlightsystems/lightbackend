#include "GeographFiasToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<GeographFias>::toJson(const GeographFiasShared& geographFias) const {
  QJsonObject geographFiasJson;
  geographFiasJson["id"] = QJsonValue::fromVariant(geographFias->getId());
  geographFiasJson["postalCode"] = QJsonValue::fromVariant(geographFias->getPostalCode());

  return geographFiasJson;
}

} // namespace light
