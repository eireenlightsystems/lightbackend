#include "SubstationToJson.h"

#include "Substation.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Substation>::toJson(const SubstationShared& substation) const {
  QJsonObject substationJson;
  substationJson["id"] = QJsonValue::fromVariant(substation->getId());
  substationJson["code"] = substation->getCode();
  return substationJson;
}
} // namespace light
