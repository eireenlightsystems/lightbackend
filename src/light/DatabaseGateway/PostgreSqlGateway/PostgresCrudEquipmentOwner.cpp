#include "PostgresCrudEquipmentOwner.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> equipmentOwnerFields{
    {"id_owner", "id_owner", true},
    {"name_owner", "name_owner", false},
};

PostgresCrud<EquipmentOwner>::PostgresCrud() {
  setFields(equipmentOwnerFields);
  setView("gateway_pkg_i.owner_vw");
}

Reader<EquipmentOwner>::Shared PostgresCrud<EquipmentOwner>::parse(const QSqlRecord& record) const {
  auto contragent = EquipmentOwnerShared::create();
  contragent->setId(record.value(getIdAlias()).value<ID>());
  contragent->setName(record.value(getFiledAlias("name_owner")).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
