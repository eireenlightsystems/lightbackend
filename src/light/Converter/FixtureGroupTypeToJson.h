#ifndef FIXTUREGROUPTYPETOJSON_H
#define FIXTUREGROUPTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<FixtureGroupType> : public ToJsonConverterTemplate<FixtureGroupType>
{
public:
  QJsonObject toJson(const FixtureGroupTypeShared& contragent) const override;
};

}
#endif // FIXTUREGROUPTYPETOJSON_H
