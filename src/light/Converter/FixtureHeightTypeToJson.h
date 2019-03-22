#ifndef FIXTUREHEIGHTTYPETOJSON_H
#define FIXTUREHEIGHTTYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<FixtureHeightType> : public ToJsonConverterTemplate<FixtureHeightType>
{
public:
  QJsonObject toJson(const FixtureHeightTypeShared& contragent) const override;
};

} // namespace light

#endif // FIXTUREHEIGHTTYPETOJSON_H
