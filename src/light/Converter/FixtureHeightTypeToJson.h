#ifndef FIXTUREHEIGHTTYPETOJSON_H
#define FIXTUREHEIGHTTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureHeightType>::toJson(const FixtureHeightTypeShared& fixtureHeightType) const;
}

#endif // FIXTUREHEIGHTTYPETOJSON_H
