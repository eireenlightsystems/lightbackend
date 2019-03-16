#include "PostgresCrudEquipmentType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<EquipmentType>::PostgresCrud() {
  setIdField("id_equipment_type");
  setFields(QStringList() << getIdField() << "code"
			  << "name"
			  << "model");
  setView("equipment_type_pkg.equipment_type_vw");
}

Reader<EquipmentType>::Shared PostgresCrud<EquipmentType>::parse(const QSqlRecord& record) const {
  auto equipmentType = EquipmentTypeShared::create();
  equipmentType->setId(record.value(0).value<ID>());
  equipmentType->setCode(record.value(1).toString());
  equipmentType->setName(record.value(2).toString());
  return equipmentType;
}

} // namespace PostgresqlGateway
} // namespace light
