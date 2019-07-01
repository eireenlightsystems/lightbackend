#include "SubstationToJson.h"

#include "Substation.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Substation>::toJson(const SubstationShared& substation) const {
  QJsonObject substationJson;
  substationJson["id"] = QJsonValue::fromVariant(substation->getId());
  substationJson["geographId"] = QJsonValue::fromVariant(substation->getGeographId());
  substationJson["geographCode"] = substation->getGeographCode();
  substationJson["code"] = substation->getCode();
  substationJson["name"] = substation->getName();
  substationJson["inn"] = substation->getInn();
  substationJson["comments"] = substation->getComments();
  substationJson["orgFormId"] = QJsonValue::fromVariant(substation->getOrgFormId());
  substationJson["orgFormCode"] = QJsonValue::fromVariant(substation->getOrgFormCode());
  substationJson["power"] = QJsonValue::fromVariant(substation->getPower());
  return substationJson;
}
} // namespace light
