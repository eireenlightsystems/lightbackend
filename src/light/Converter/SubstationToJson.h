#ifndef SUBSTATIONTOJSON_H
#define SUBSTATIONTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Substation> : public ToJsonConverterTemplate<Substation>
{
public:
  QJsonObject toJson(const SubstationShared& contragent) const override;
};

}

#endif // SUBSTATIONTOJSON_H
