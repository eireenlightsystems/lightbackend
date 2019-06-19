#include "PostgresCrudFixtureType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureTypeFields{
    {"id_equipment_type", "id_fixture_type", true},
    {"code", "code_fixture_type", false},
    {"name", "name_fixture_type", false},
    {"model", "model_fixture_type", false},
    {"comments", "comments_fixture_type", false},

    {"height", "height_fixture_type", false},
    {"width", "width_fixture_type", false},
    {"weight", "weight_fixture_type", false},
    {"length", "length_fixture_type", false},

    {"countlamp", "countlamp_fixture_type", false},
    {"power", "power_fixture_type", false},
    {"cos", "cos_fixture_type", false},
    {"ip", "ip_fixture_type", false},
    {"efficiency", "efficiency_fixture_type", false},
};

PostgresCrud<FixtureType>::PostgresCrud() {
  setFields(fixtureTypeFields);
  setView("fixture_type_pkg_i.fixture_type_vwf()");
  setInsertSql("select fixture_type_pkg_i.save(:action, :id_equipment_type, "
	       ":code, :name, :model, "
	       ":comments, "
	       ":height, :width, :weight,"
	       ":length, :countlamp, :power,"
	       ":cos, :ip, :efficiency)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select fixture_type_pkg_i.del(:id)");
}

Reader<FixtureType>::Shared PostgresCrud<FixtureType>::parse(const QSqlRecord& record) const {
  auto fixtureType = FixtureTypeShared::create();
  fixtureType->setId(record.value(getIdAlias()).value<ID>());
  fixtureType->setCode(record.value(getFieldAlias("code")).toString());
  fixtureType->setName(record.value(getFieldAlias("name")).toString());
  fixtureType->setModel(record.value(getFieldAlias("model")).toString());
  fixtureType->setComment(record.value(getFieldAlias("comments")).toString());

  fixtureType->setHeight(record.value(getFieldAlias("height")).toDouble());
  fixtureType->setWidth(record.value(getFieldAlias("width")).toDouble());
  fixtureType->setWeight(record.value(getFieldAlias("weight")).toDouble());
  fixtureType->setLength(record.value(getFieldAlias("length")).toDouble());

  fixtureType->setCountlamp(record.value(getFieldAlias("countlamp")).toDouble());
  fixtureType->setPower(record.value(getFieldAlias("power")).toDouble());
  fixtureType->setCos(record.value(getFieldAlias("cos")).toDouble());
  fixtureType->setIp(record.value(getFieldAlias("ip")).toDouble());
  fixtureType->setEfficiency(record.value(getFieldAlias("efficiency")).toDouble());
  return fixtureType;
}

BindParamsType PostgresCrud<FixtureType>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<FixtureType>::getInsertParams(const Editor::Shared &fixtureType) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_equipment_type", QVariant()},
      {":code", fixtureType->getCode()},
      {":name", fixtureType->getName()},
      {":model", fixtureType->getModel()},
      {":comments", fixtureType->getComment()},

      {":height", fixtureType->getHeight()},
      {":width", fixtureType->getWidth()},
      {":weight", fixtureType->getWeight()},
      {":length", fixtureType->getLength()},

      {":countlamp", fixtureType->getCountlamp()},
      {":power", fixtureType->getPower()},
      {":cos", fixtureType->getCos()},
      {":ip", fixtureType->getIp()},
      {":efficiency", fixtureType->getEfficiency()},
  };
}

BindParamsType PostgresCrud<FixtureType>::getUpdateParams(const Editor::Shared &fixtureType) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_equipment_type", fixtureType->getId()},
      {":code", fixtureType->getCode()},
      {":name", fixtureType->getName()},
      {":model", fixtureType->getModel()},
      {":comments", fixtureType->getComment()},

      {":height", fixtureType->getHeight()},
      {":width", fixtureType->getWidth()},
      {":weight", fixtureType->getWeight()},
      {":length", fixtureType->getLength()},

      {":countlamp", fixtureType->getCountlamp()},
      {":power", fixtureType->getPower()},
      {":cos", fixtureType->getCos()},
      {":ip", fixtureType->getIp()},
      {":efficiency", fixtureType->getEfficiency()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
