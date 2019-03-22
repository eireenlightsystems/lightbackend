#ifndef FIXTURETYPETOJSON_H
#define FIXTURETYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<FixtureType> : public ToJsonConverterTemplate<FixtureType>
{
public:
  QJsonObject toJson(const FixtureTypeShared& contragent) const override;
};

}

#endif // FIXTURETYPETOJSON_H
