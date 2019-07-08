#include "SubstationToJson.h"

#include "Substation.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "ContragentToJson.h"

namespace light {

QJsonObject ToJsonConverter<Substation>::toJson(const SubstationShared& substation) const {
  ToJsonConverter<Contragent> contragentToJsonConverter;
  QJsonObject substationJson = contragentToJsonConverter.toJson(substation);
  substationJson["orgFormId"] = QJsonValue::fromVariant(substation->getOrgFormId());
  substationJson["orgFormCode"] = QJsonValue::fromVariant(substation->getOrgFormCode());
  substationJson["power"] = QJsonValue::fromVariant(substation->getPower());
  return substationJson;
}
} // namespace light
