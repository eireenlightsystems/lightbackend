#include "PersonToJson.h"

#include "Person.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Person>::toJson(const PersonShared& person) const {
  QJsonObject personJson;
  personJson["id"] = QJsonValue::fromVariant(person->getId());
  personJson["geographId"] = QJsonValue::fromVariant(person->getGeographId());
  personJson["geographCode"] = person->getGeographCode();
  personJson["code"] = person->getCode();
  personJson["name"] = person->getName();
  personJson["inn"] = person->getInn();
  personJson["comments"] = person->getComments();
  personJson["name_first"] = person->getNameFirst();
  personJson["name_second"] = person->getNameSecond();
  personJson["name_third"] = person->getNameThird();
  return personJson;
}

} // namespace light

