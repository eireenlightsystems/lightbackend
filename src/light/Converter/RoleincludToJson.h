#ifndef ROLEINCLUDTOJSON_H
#define ROLEINCLUDTOJSON_H


#include "Roleinclud.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Roleinclud> : public ToJsonConverterTemplate<Roleinclud>
{
public:
  QJsonObject toJson(const RoleincludShared& roleinclud) const override;
};

} // namespace light

#endif // ROLEINCLUDTOJSON_H
