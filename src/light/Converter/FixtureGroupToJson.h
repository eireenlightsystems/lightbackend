#ifndef FIXTUREGROUPTOJSON_H
#define FIXTUREGROUPTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureGroup>::toJson(const FixtureGroupShared& fixtureGroup) const;

}

#endif // FIXTUREGROUPTOJSON_H
