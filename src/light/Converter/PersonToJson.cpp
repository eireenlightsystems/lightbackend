#include "PersonToJson.h"

#include "Person.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "ContragentToJson.h"

namespace light {

QJsonObject ToJsonConverter<Person>::toJson(const PersonShared& person) const {
  ToJsonConverter<Contragent> contragentToJsonConverter;
  QJsonObject personJson = contragentToJsonConverter.toJson(person);
  personJson["nameFirst"] = person->getNameFirst();
  personJson["nameSecond"] = person->getNameSecond();
  personJson["nameThird"] = person->getNameThird();
  return personJson;
}

} // namespace light

