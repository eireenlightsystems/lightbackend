#include "PostgresCrudFixtureGroupType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureGroupTypeFields{
    {"id_fixture_group_type", "id_fixture_group_type", true},
    {"name_fixture_group_type", "name_fixture_group_type", false},
};

PostgresCrud<FixtureGroupType>::PostgresCrud() {
  setFields(fixtureGroupTypeFields);
  setView("fixture_group_pkg_i.fixture_group_type_vw");
}

Reader<FixtureGroupType>::Shared PostgresCrud<FixtureGroupType>::parse(const QSqlRecord& record) const {
  auto type = FixtureGroupTypeShared::create();
  type->setId(record.value(getIdAlias()).value<ID>());
  type->setName(record.value(getFieldAlias("name_fixture_group_type")).toString());
  return type;
}

} // namespace PostgresqlGateway
} // namespace light
