#ifndef CONTRACTTYPETOJSON_H
#define CONTRACTTYPETOJSON_H


#include "ContractType.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<ContractType> : public ToJsonConverterTemplate<ContractType>
{
public:
  QJsonObject toJson(const ContractTypeShared& contract) const override;
};

} // namespace light

#endif // CONTRACTTYPETOJSON_H
