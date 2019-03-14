#ifndef FIXTURETYPETOJSON_H
#define FIXTURETYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureType>::toJson(const FixtureTypeShared& fixtureType) const;
}

#endif // FIXTURETYPETOJSON_H
