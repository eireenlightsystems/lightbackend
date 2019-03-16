#include "PostgresCrudEquipmentOwner.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<EquipmentOwner>::PostgresCrud() {
  setIdField("id_owner");
  setFields(QStringList() << getIdField() << "name_owner");
  setView("gateway_pkg_i.owner_vw");
}

Reader<EquipmentOwner>::Shared PostgresCrud<EquipmentOwner>::parse(const QSqlRecord& record) const {
  auto contragent = EquipmentOwnerShared::create();
  contragent->setId(record.value(0).value<ID>());
  contragent->setName(record.value(1).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
