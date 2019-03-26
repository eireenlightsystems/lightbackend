#ifndef CONTRACTSTOJSON_H
#define CONTRACTSTOJSON_H

#include "Contract.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Contract> : public ToJsonConverterTemplate<Contract>
{
public:
  QJsonObject toJson(const ContractShared& contract) const override;
};

} // namespace light

#endif // CONTRACTSTOJSON_H
