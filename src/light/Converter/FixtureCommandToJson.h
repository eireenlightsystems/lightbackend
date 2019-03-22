#ifndef FIXTURECOMMANDTOJSON_H
#define FIXTURECOMMANDTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureCommand>::toJson(const FixtureCommandShared& command) const;

template <>
QJsonObject
ToJsonConverter<FixtureLightLevelCommand>::toJson(const FixtureLightLevelCommandShared& lightLevelCommand) const;

template <>
QJsonObject
ToJsonConverter<FixtureLightSpeedCommand>::toJson(const FixtureLightSpeedCommandShared& lightSpeedCommand) const;
} // namespace light

#endif // FIXTURECOMMANDTOJSON_H
