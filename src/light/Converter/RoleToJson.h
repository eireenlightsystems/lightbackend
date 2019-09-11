#ifndef ROLETOJSON_H
#define ROLETOJSON_H


#include "Role.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Role> : public ToJsonConverterTemplate<Role>
{
public:
  QJsonObject toJson(const RoleShared& role) const override;
};

} // namespace light

#endif // ROLETOJSON_H
