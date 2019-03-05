#ifndef POSTGRESCRUDEQUIPMENTTYPE_H
#define POSTGRESCRUDEQUIPMENTTYPE_H

#include "EquipmentType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
EquipmentTypeSharedList PostgresCrud<EquipmentType>::sel(const IDList& ids) const;

template <>
EquipmentTypeShared PostgresCrud<EquipmentType>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDEQUIPMENTTYPE_H
