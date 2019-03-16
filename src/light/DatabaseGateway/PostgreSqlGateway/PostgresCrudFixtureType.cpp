#include "PostgresCrudFixtureType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<FixtureType>::PostgresCrud() {
  setIdField("id_fixture_type");
  setFields(QStringList() << getIdField() << "code_fixture_type"
			  << "model_fixture_type"
			  << "length"
			  << "width"
			  << "height");
  setView("fixture_pkg_i.fixture_type_vw");
}

Reader<FixtureType>::Shared PostgresCrud<FixtureType>::parse(const QSqlRecord& record) const {
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
