#include "PostgresCrudFixtureHeightType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<FixtureHeightType>::PostgresCrud() {
  setIdField("id_height_type");
  setFields(QStringList() << getIdField() << "code"
			  << "name");
  setView("fixture_pkg_i.height_type_vw");
}

Reader<FixtureHeightType>::Shared PostgresCrud<FixtureHeightType>::parse(const QSqlRecord& record) const {
  auto fixtureType = FixtureHeightTypeShared::create();
  fixtureType->setId(record.value(0).value<ID>());
  fixtureType->setCode(record.value(1).toString());
  fixtureType->setName(record.value(2).toString());
  return fixtureType;
}

} // namespace PostgresqlGateway
} // namespace light
