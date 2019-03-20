#include "PostgresCrudEquipmentType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> equipmentTypeFields{
    {"id_equipment_type", "id_equipment_type", true},
    {"code", "code_equipment_type", false},
    {"name", "name_equipment_type", false},
    {"model", "model_equipment_type", false},
};

PostgresCrud<EquipmentType>::PostgresCrud() {
  setFields(equipmentTypeFields);
  setView("equipment_type_pkg.equipment_type_vw");
}

Reader<EquipmentType>::Shared PostgresCrud<EquipmentType>::parse(const QSqlRecord& record) const {
  auto equipmentType = EquipmentTypeShared::create();
  equipmentType->setId(record.value(getIdAlias()).value<ID>());
  equipmentType->setCode(record.value(getFieldAlias("code_equipment_type")).toString());
  equipmentType->setName(record.value(getFieldAlias("name_equipment_type")).toString());
  equipmentType->setModel(record.value(getFieldAlias("model_equipment_type")).toString());
  return equipmentType;
}

} // namespace PostgresqlGateway
} // namespace light
