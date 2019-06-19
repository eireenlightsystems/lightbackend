#ifndef PERSONTOJSON_H
#define PERSONTOJSON_H

#include "ToJsonConverter.h"
#include "Person.h"

namespace light {

template <>
class ToJsonConverter<Person> : public ToJsonConverterTemplate<Person>
{
public:
  QJsonObject toJson(const PersonShared& person) const override;
};

} // namespace light

#endif // PERSONTOJSON_H
