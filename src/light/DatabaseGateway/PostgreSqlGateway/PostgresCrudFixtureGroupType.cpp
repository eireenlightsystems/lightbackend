#include "PostgresCrudFixtureGroupType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<FixtureGroupType>::PostgresCrud() {
  setIdField("id_fixture_group_type");
  setFields(QStringList() << getIdField() << "name_fixture_group_type");
  setView("fixture_group_pkg_i.fixture_group_type_vw");
}

Reader<FixtureGroupType>::Shared PostgresCrud<FixtureGroupType>::parse(const QSqlRecord& record) const {
  auto type = FixtureGroupTypeShared::create();
  type->setId(record.value(0).value<ID>());
  type->setName(record.value(1).toString());
  return type;
}

} // namespace PostgresqlGateway
} // namespace light
