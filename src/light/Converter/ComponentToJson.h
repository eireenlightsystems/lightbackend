#ifndef COMPONENTTOJSON_H
#define COMPONENTTOJSON_H


#include "Component.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Component> : public ToJsonConverterTemplate<Component>
{
public:
  QJsonObject toJson(const ComponentShared& component) const override;
};

} // namespace light


#endif // COMPONENTTOJSON_H
