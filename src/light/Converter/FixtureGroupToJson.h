#ifndef FIXTUREGROUPTOJSON_H
#define FIXTUREGROUPTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<FixtureGroup> : public ToJsonConverterTemplate<FixtureGroup>
{
public:
  QJsonObject toJson(const FixtureGroupShared& contragent) const override;
};

}

#endif // FIXTUREGROUPTOJSON_H
