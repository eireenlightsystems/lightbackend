#include "PostgresCrudGeograph.h"

#include <QElapsedTimer>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
GeographSharedList PostgresCrud<Geograph>::sel<>() const {
  GeographSharedList result;
  const QString sql = "select id_geograph, code, name, fullname "
		      "from geograph_pkg.geograph_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
template <>
GeographSharedList PostgresCrud<Geograph>::sel<QVariantHash>(const QVariantHash filters) const {
  if(filters.isEmpty()) {
    return  sel();
  }

  return GeographSharedList();
}

template <>
GeographSharedList PostgresCrud<Geograph>::sel(const IDList& ids) const {
  GeographSharedList result;
  const QString sql = "select id_geograph, code, name, fullname "
		      "from geograph_pkg.geograph_vw "
		      "where id_geograph = :id_geograph";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_geograph", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
GeographShared PostgresCrud<Geograph>::parse(const QSqlRecord& record) const {
  auto geograph = GeographShared::create();
  geograph->setId(record.value(0).value<ID>());
  geograph->setCode(record.value(1).toString());
  geograph->setName(record.value(2).toString());
  geograph->setFullName(record.value(3).toString());
  return geograph;
}

} // namespace PostgresqlGateway
} // namespace light
