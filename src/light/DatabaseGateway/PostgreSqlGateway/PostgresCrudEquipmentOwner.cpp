#include "PostgresCrudEquipmentOwner.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel<>() const {
  EquipmentOwnerSharedList result;
  const QString sql = "select id_owner, code_owner, name_owner "
		      "from gateway_pkg_i.owner_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel(const IDList& ids) const {
  EquipmentOwnerSharedList result;
  const QString sql = "select id_owner, code_owner, name_owner "
		      "from gateway_pkg_i.owner_vw "
		      "where id_owner = :id_owner";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_owner", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
EquipmentOwnerShared PostgresCrud<EquipmentOwner>::parse(const QSqlRecord& record) const {
  auto contragent = EquipmentOwnerShared::create();
  contragent->setId(record.value(0).value<ID>());
  contragent->setCode(record.value(1).toString());
  contragent->setName(record.value(2).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
