#ifndef GATEWAYOWNERTOJSON_H
#define GATEWAYOWNERTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<EquipmentOwner> : public ToJsonConverterTemplate<EquipmentOwner>
{
public:
  QJsonObject toJson(const EquipmentOwnerShared& contragent) const override;
};

}

#endif // GATEWAYOWNERTOJSON_H
