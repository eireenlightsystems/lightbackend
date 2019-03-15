#include "PostgresCrudSubstation.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
SubstationSharedList PostgresCrud<Substation>::sel<>() const {
  SubstationSharedList result;
  const QString sql = "select id_substation, code, name, power "
		      "from fixture_pkg_i.substation_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
template <>
SubstationSharedList PostgresCrud<Substation>::sel<QVariantHash>(const QVariantHash filters) const {
  if(filters.isEmpty()) {
    return sel();
  }

  return SubstationSharedList();
}

template <>
SubstationSharedList PostgresCrud<Substation>::sel(const IDList& ids) const {
  SubstationSharedList result;
  const QString sql = "select id_substation, code, name, power "
		      "from fixture_pkg_i.substation_vw "
		      "where id_substation = :id_substation";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_substation", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
SubstationShared PostgresCrud<Substation>::parse(const QSqlRecord& record) const {
  auto substation = SubstationShared::create();
  substation->setId(record.value(0).value<ID>());
  substation->setCode(record.value(1).toString());
  substation->setName(record.value(2).toString());
  substation->setPower(record.value(3).toDouble());
  return substation;
}

} // namespace PostgresqlGateway
} // namespace light
