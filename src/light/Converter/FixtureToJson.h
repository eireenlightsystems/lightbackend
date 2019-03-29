#ifndef FIXTURETOJSON_H
#define FIXTURETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Fixture> : public ToJsonConverterTemplate<Fixture>
{
public:
  QJsonObject toJson(const FixtureShared& fixture) const override;
};

template <>
class ToJsonConverter<FixtureInGroup> : public ToJsonConverterTemplate<FixtureInGroup>
{
public:
  QJsonObject toJson(const FixtureInGroupShared& fixtureInGroup) const override;
};

template <>
class ToJsonConverter<FixtureContract> : public ToJsonConverterTemplate<FixtureContract>
{
public:
  QJsonObject toJson(const FixtureContractShared& fixtureContract) const override;
};

template <>
class ToJsonConverter<FixtureOwner> : public ToJsonConverterTemplate<FixtureOwner>
{
public:
  QJsonObject toJson(const FixtureOwnerShared& fixtureOwner) const override;
};

template <>
class ToJsonConverter<FixtureInstaller> : public ToJsonConverterTemplate<FixtureInstaller>
{
public:
  QJsonObject toJson(const FixtureInstallerShared& fixtureInstaller) const override;
};

} // namespace light

#endif // FIXTURETOJSON_H
