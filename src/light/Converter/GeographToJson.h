#ifndef GROGRAPHTOJSON_H
#define GROGRAPHTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Geograph> : public ToJsonConverterTemplate<Geograph>
{
public:
  QJsonObject toJson(const GeographShared& contragent) const override;
};


} // namespace light

#endif // GROGRAPHTOJSON_H
