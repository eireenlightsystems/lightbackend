#include "FixtureTypeToJson.h"

#include "FixtureType.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<FixtureType>::toJson(const FixtureTypeShared& fixtureType) const {
  QJsonObject fixtureTypeJson;
  fixtureTypeJson["id"] = QJsonValue::fromVariant(fixtureType->getId());
  fixtureTypeJson["code"] = fixtureType->getCode();
  fixtureTypeJson["name"] = fixtureType->getName();
  fixtureTypeJson["model"] = fixtureType->getModel();
  fixtureTypeJson["comments"] = fixtureType->getComment();

  fixtureTypeJson["height"] = fixtureType->getHeight();
  fixtureTypeJson["width"] = fixtureType->getWidth();
  fixtureTypeJson["weight"] = fixtureType->getWeight();
  fixtureTypeJson["length"] = fixtureType->getLength();

  fixtureTypeJson["countlamp"] = fixtureType->getCountlamp();
  fixtureTypeJson["power"] = fixtureType->getPower();
  fixtureTypeJson["cos"] = fixtureType->getCos();
  fixtureTypeJson["ip"] = fixtureType->getIp();
  fixtureTypeJson["efficiency"] = fixtureType->getEfficiency();

  return fixtureTypeJson;
}

} // namespace light
