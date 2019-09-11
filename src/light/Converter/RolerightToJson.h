#ifndef ROLERIGHTTOJSON_H
#define ROLERIGHTTOJSON_H


#include "Roleright.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Roleright> : public ToJsonConverterTemplate<Roleright>
{
public:
  QJsonObject toJson(const RolerightShared& roleright) const override;
};

} // namespace light

#endif // ROLERIGHTTOJSON_H
