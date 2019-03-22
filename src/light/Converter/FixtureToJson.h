#ifndef FIXTURETOJSON_H
#define FIXTURETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Fixture> : public ToJsonConverterTemplate<Fixture>
{
public:
  QJsonObject toJson(const FixtureShared& contragent) const override;
};

}

#endif // FIXTURETOJSON_H
