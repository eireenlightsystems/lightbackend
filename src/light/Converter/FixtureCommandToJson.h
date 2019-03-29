#ifndef FIXTURECOMMANDTOJSON_H
#define FIXTURECOMMANDTOJSON_H

#include "FixtureCommand.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<FixtureCommand> : public ToJsonConverterTemplate<FixtureCommand>
{
public:
  QJsonObject toJson(const FixtureCommandShared& command) const override;
};

template <>
class ToJsonConverter<FixtureCommandType> : public ToJsonConverterTemplate<FixtureCommandType>
{
public:
  QJsonObject toJson(const FixtureCommandTypeShared& type) const override;
};

template <>
class ToJsonConverter<FixtureLightLevelCommand> : public ToJsonConverterTemplate<FixtureLightLevelCommand>
{
public:
  QJsonObject toJson(const FixtureLightLevelCommandShared& lightLevelCommand) const override;
};

template <>
class ToJsonConverter<FixtureLightLevelCommandType> : public ToJsonConverterTemplate<FixtureLightLevelCommandType>
{
public:
  QJsonObject toJson(const FixtureLightLevelCommandTypeShared& type) const override;
};

template <>
class ToJsonConverter<FixtureLightSpeedCommand> : public ToJsonConverterTemplate<FixtureLightSpeedCommand>
{
public:
  QJsonObject toJson(const FixtureLightSpeedCommandShared& speedCommand) const override;
};

template <>
class ToJsonConverter<FixtureLightSpeedCommandType> : public ToJsonConverterTemplate<FixtureLightSpeedCommandType>
{
public:
  QJsonObject toJson(const FixtureLightSpeedCommandTypeShared& type) const override;
};

template <>
class ToJsonConverter<FixtureCommandStatus> : public ToJsonConverterTemplate<FixtureCommandStatus>
{
public:
  QJsonObject toJson(const FixtureCommandStatusShared& status) const override;
};

} // namespace light

#endif // FIXTURECOMMANDTOJSON_H
