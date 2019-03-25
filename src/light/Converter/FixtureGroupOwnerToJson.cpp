#include "FixtureGroupOwnerToJson.h"

#include "ContragentToJson.h"
#include "FixtureGroup.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<FixtureGroupOwner>::toJson(const FixtureGroupOwnerShared& fixtureGroupOwner) const {
  ToJsonConverter<Contragent> contragentConverter;
  return contragentConverter.toJson(fixtureGroupOwner.dynamicCast<Contragent>());
}

} // namespace light
