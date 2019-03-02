#include "PostgresCrudEquipmentType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
EquipmentTypeSharedList PostgresCrud<EquipmentType>::sel<const IDList&>(const IDList& ids) const {
  EquipmentTypeSharedList result;
  const QString sql = "select id_equipment_type, code, name, model "
		      "from equipment_type_pkg.equipment_type_vw "
		      "where id_equipment_type = :id_equipment_type";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_equipment_type", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
EquipmentTypeShared PostgresCrud<EquipmentType>::parse(const QSqlRecord& record) const {
  auto equipmentType = EquipmentTypeShared::create();
  equipmentType->setId(record.value(0).value<ID>());
  equipmentType->setCode(record.value(1).toString());
  equipmentType->setName(record.value(2).toString());
  return equipmentType;
}

} // namespace PostgresqlGateway
} // namespace light
