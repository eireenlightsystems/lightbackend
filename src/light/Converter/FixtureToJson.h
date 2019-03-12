#ifndef FIXTURETOJSON_H
#define FIXTURETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<Fixture>::toJson(const FixtureShared& fixture) const;
}

#endif // FIXTURETOJSON_H
