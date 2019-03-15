#ifndef POSTGRESCRUDEQUIPMENTOWNER_H
#define POSTGRESCRUDEQUIPMENTOWNER_H

#include "EquipmentOwner.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel<>() const;

template <>
template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel<QVariantHash>(const QVariantHash filters) const;

template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel(const IDList& ids) const;

template <>
EquipmentOwnerShared PostgresCrud<EquipmentOwner>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDEQUIPMENTOWNER_H
