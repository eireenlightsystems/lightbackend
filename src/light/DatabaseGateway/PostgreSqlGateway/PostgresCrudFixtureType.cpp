#include "PostgresCrudFixtureType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureTypeFields{
    {"id_fixture_type", "id_fixture_type", true},
    {"code_fixture_type", "code_fixture_type", false},
    {"model_fixture_type", "model_fixture_type", false},
    {"length", "length_fixture_type", false},
    {"width", "width_fixture_type", false},
    {"height", "height_fixture_type", false},
    {"weight", "weight_fixture_type", false},
};

PostgresCrud<FixtureType>::PostgresCrud() {
  setFields(fixtureTypeFields);
  setView("fixture_pkg_i.fixture_type_vw");
}

Reader<FixtureType>::Shared PostgresCrud<FixtureType>::parse(const QSqlRecord& record) const {
  auto fixtureType = FixtureTypeShared::create();
  fixtureType->setId(record.value(getIdAlias()).value<ID>());
  fixtureType->setCode(record.value(getFieldAlias("code_fixture_type")).toString());
  fixtureType->setModel(record.value(getFieldAlias("model_fixture_type")).toString());
  fixtureType->setLenght(record.value(getFieldAlias("length_fixture_type")).toDouble());
  fixtureType->setWidth(record.value(getFieldAlias("width_fixture_type")).toDouble());
  fixtureType->setHeight(record.value(getFieldAlias("height_fixture_type")).toDouble());
  fixtureType->setWeight(record.value(getFieldAlias("weight_fixture_type")).toDouble());
  return fixtureType;
}

} // namespace PostgresqlGateway
} // namespace light
