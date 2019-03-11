#ifndef FIXTUREGROUPTYPETOJSON_H
#define FIXTUREGROUPTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureGroupType>::toJson(const FixtureGroupTypeShared& fixtureGroupType) const;

}
#endif // FIXTUREGROUPTYPETOJSON_H
