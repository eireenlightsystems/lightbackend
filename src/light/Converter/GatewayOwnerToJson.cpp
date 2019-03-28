#include "GatewayOwnerToJson.h"

#include "ContragentToJson.h"
#include "EquipmentOwner.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<EquipmentOwner>::toJson(const EquipmentOwnerShared& equipmentOwner) const {
  ToJsonConverter<Contragent> contragentConverter;
  return contragentConverter.toJson(equipmentOwner.dynamicCast<Contragent>());
}

} // namespace light
