#ifndef POSTGRESCRUDEQUIPMENTTYPE_H
#define POSTGRESCRUDEQUIPMENTTYPE_H


#include "PostgresCrud.h"
#include "EquipmentType.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
EquipmentTypeSharedList PostgresCrud<EquipmentType>::sel<const IDList&>(const IDList& ids) const;

template <>
EquipmentTypeShared PostgresCrud<EquipmentType>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDEQUIPMENTTYPE_H
