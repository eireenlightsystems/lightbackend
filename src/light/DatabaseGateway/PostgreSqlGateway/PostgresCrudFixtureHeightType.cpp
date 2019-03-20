#include "PostgresCrudFixtureHeightType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureHeightTypeFields{
    {"id_height_type", "id_height_type", true},
    {"code", "code_height_type", false},
    {"name", "name_height_type", false},
};

PostgresCrud<FixtureHeightType>::PostgresCrud() {
  setFields(fixtureHeightTypeFields);
  setView("fixture_pkg_i.height_type_vw");
}

Reader<FixtureHeightType>::Shared PostgresCrud<FixtureHeightType>::parse(const QSqlRecord& record) const {
  auto fixtureType = FixtureHeightTypeShared::create();
  fixtureType->setId(record.value(getIdAlias()).value<ID>());
  fixtureType->setCode(record.value(getFieldAlias("code_height_type")).toString());
  fixtureType->setName(record.value(getFieldAlias("name_height_type")).toString());
  return fixtureType;
}

} // namespace PostgresqlGateway
} // namespace light
