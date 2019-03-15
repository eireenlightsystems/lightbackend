#include "PostgresCrudEquipmentOwner.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel<>() const {
  EquipmentOwnerSharedList result;
  const QString sql = "select id_owner, name_owner "
		      "from gateway_pkg_i.owner_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel<QVariantHash>(const QVariantHash filters) const {
  if(filters.isEmpty()) {
    return  sel();
  }

  return EquipmentOwnerSharedList();
}

template <>
EquipmentOwnerSharedList PostgresCrud<EquipmentOwner>::sel(const IDList& ids) const {
  EquipmentOwnerSharedList result;
  const QString sql = "select id_owner, name_owner "
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
  contragent->setName(record.value(1).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
