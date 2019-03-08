#ifndef SUBSTATIONTOJSON_H
#define SUBSTATIONTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<Substation>::toJson(const SubstationShared& substation) const;
}

#endif // SUBSTATIONTOJSON_H
