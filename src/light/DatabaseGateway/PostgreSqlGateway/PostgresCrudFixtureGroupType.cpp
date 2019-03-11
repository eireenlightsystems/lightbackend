#include "PostgresCrudFixtureGroupType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureGroupTypeSharedList PostgresCrud<FixtureGroupType>::sel<>() const {
  FixtureGroupTypeSharedList result;
  const QString sql = "select id_fixture_group_type, name_fixture_group_type "
		      "from fixture_group_pkg_i.fixture_group_type_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
FixtureGroupTypeSharedList PostgresCrud<FixtureGroupType>::sel(const IDList& ids) const {
  FixtureGroupTypeSharedList result;
  const QString sql = "select id_fixture_group_type, name_fixture_group_type "
		      "from fixture_group_pkg_i.fixture_group_type_vw "
		      "where id_fixture_group_type = :id_fixture_group_type";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_fixture_group_type", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
FixtureGroupTypeShared PostgresCrud<FixtureGroupType>::parse(const QSqlRecord& record) const {
  auto type = FixtureGroupTypeShared::create();
  type->setId(record.value(0).value<ID>());
  type->setName(record.value(1).toString());
  return type;
}

} // namespace PostgresqlGateway
} // namespace light
