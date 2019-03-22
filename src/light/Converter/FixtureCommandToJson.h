#ifndef FIXTURECOMMANDTOJSON_H
#define FIXTURECOMMANDTOJSON_H

#include "ToJsonConverter.h"
#include "FixtureCommand.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"

namespace light {

template <>
class ToJsonConverter<FixtureCommand> : public ToJsonConverterTemplate<FixtureCommand>
{
public:
  QJsonObject toJson(const FixtureCommandShared& contragent) const override;
};

template <>
class ToJsonConverter<FixtureLightLevelCommand> : public ToJsonConverterTemplate<FixtureLightLevelCommand>
{
public:
  QJsonObject toJson(const FixtureLightLevelCommandShared& contragent) const override;
};

template <>
class ToJsonConverter<FixtureLightSpeedCommand> : public ToJsonConverterTemplate<FixtureLightSpeedCommand>
{
public:
  QJsonObject toJson(const FixtureLightSpeedCommandShared& contragent) const override;
};

} // namespace light

#endif // FIXTURECOMMANDTOJSON_H
