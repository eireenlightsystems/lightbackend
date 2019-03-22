#ifndef CONTRAGENTTOJSON_H
#define CONTRAGENTTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Contragent> : public ToJsonConverterTemplate<Contragent>
{
public:
  QJsonObject toJson(const ContragentShared& contragent) const override;
};

} // namespace light

#endif // CONTRAGENTTOJSON_H
