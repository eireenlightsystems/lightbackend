#include "PostgresCrudGeograph.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
GeographSharedList PostgresCrud<Geograph>::sel(const IDList& ids) const {
  GeographSharedList result;
  const QString sql = "select id_geograph, code, name "
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
  return geograph;
}

} // namespace PostgresqlGateway
} // namespace light
