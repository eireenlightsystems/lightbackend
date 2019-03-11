#ifndef CONTRAGENTTOJSON_H
#define CONTRAGENTTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<Contragent>::toJson(const ContragentShared& contragent) const;
}

#endif // CONTRAGENTTOJSON_H
