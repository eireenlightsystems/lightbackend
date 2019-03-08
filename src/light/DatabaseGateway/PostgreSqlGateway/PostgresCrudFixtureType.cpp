#include "PostgresCrudFixtureType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureTypeSharedList PostgresCrud<FixtureType>::sel<>() const {
  FixtureTypeSharedList result;
  const QString sql = "select id_fixture_type, code_fixture_type, model_fixture_type, length, width, height "
		      "from fixture_pkg_i.fixture_type_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
FixtureTypeSharedList PostgresCrud<FixtureType>::sel(const IDList& ids) const {
  FixtureTypeSharedList result;
  const QString sql = "select id_fixture_type, code_fixture_type, model_fixture_type, length, width, height "
		      "from fixture_pkg_i.fixture_type_vw "
		      "where id_fixture_type = :id_fixture_type";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_fixture_type", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
FixtureTypeShared PostgresCrud<FixtureType>::parse(const QSqlRecord& record) const {
  auto fixtureType = FixtureTypeShared::create();
  fixtureType->setId(record.value(0).value<ID>());
  fixtureType->setCode(record.value(1).toString());
  fixtureType->setModel(record.value(2).toString());
  fixtureType->setLenght(record.value(3).toDouble());
  fixtureType->setWidth(record.value(4).toDouble());
  fixtureType->setHeight(record.value(5).toDouble());
  fixtureType->setWeight(record.value(6).toDouble());
  return fixtureType;
}

} // namespace PostgresqlGateway
} // namespace light
