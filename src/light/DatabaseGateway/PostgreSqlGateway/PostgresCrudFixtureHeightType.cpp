#include "PostgresCrudFixtureHeightType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureHeightTypeSharedList PostgresCrud<FixtureHeightType>::sel<>() const {
  FixtureHeightTypeSharedList result;
  const QString sql = "select id_height_type, code, name "
		      "from fixture_pkg_i.height_type_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
template <>
FixtureHeightTypeSharedList PostgresCrud<FixtureHeightType>::sel<QVariantHash>(const QVariantHash filters) const {
  if (filters.isEmpty()) {
    return sel();
  }

  return FixtureHeightTypeSharedList();
}

template <>
FixtureHeightTypeSharedList PostgresCrud<FixtureHeightType>::sel(const IDList& ids) const {
  FixtureHeightTypeSharedList result;
  const QString sql = "select id_height_type, code, name "
		      "from fixture_pkg_i.height_type_vw "
		      "where id_height_type = :id_height_type";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_height_type", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
FixtureHeightTypeShared PostgresCrud<FixtureHeightType>::parse(const QSqlRecord& record) const {
  auto fixtureType = FixtureHeightTypeShared::create();
  fixtureType->setId(record.value(0).value<ID>());
  fixtureType->setCode(record.value(1).toString());
  fixtureType->setName(record.value(2).toString());
  return fixtureType;
}

} // namespace PostgresqlGateway
} // namespace light
