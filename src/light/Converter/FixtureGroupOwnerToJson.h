#ifndef FIXTUREGROUPOWNERTOJSON_H
#define FIXTUREGROUPOWNERTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<FixtureGroupOwner> : public ToJsonConverterTemplate<FixtureGroupOwner>
{
public:
  QJsonObject toJson(const FixtureGroupOwnerShared& fixtureGroupOwner) const override;
};

} // namespace light

#endif // FIXTUREGROUPOWNERTOJSON_H
