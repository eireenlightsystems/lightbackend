#ifndef GATEWAYOWNERTOJSON_H
#define GATEWAYOWNERTOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<EquipmentOwner>::toJson(const EquipmentOwnerShared& equipmentOwner) const;
}

#endif // GATEWAYOWNERTOJSON_H
