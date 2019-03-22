#include "SchedulerFixturePostgresCrud.h"

#include "CommandsSchedulerTypeDefs.h"
#include "NotImplementedException.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureFields{
    {"id_fixture", "id_fixture", true},
    {"work_level", "work_level", false},
    {"standby_level", "standby_level", false},
    {"speed_zero_to_full", "speed_zero_to_full", false},
    {"speed_full_to_zero", "speed_full_to_zero", false},
};

PostgresCrud<CommandsScheduler::SchedulerFixture>::PostgresCrud() {
  setFields(fixtureFields);
  setView("fixture_pkg_i.fixture_vwf(:id_geograph, :id_owner, :id_fixture_type, :id_substation, :id_mode, "
	  ":id_contract, :id_node)");
  setUpdateSql("select fixture_pkg_i.set_speed_full_to_zero(:id_fixture, :speed_full_to_zero), "
	       "fixture_pkg_i.set_speed_zero_to_full(:id_fixture, :speed_zero_to_full), "
	       "fixture_pkg_i.set_standby_level(:id_fixture, :standby_level),"
	       "fixture_pkg_i.set_work_level(:id_fixture, :work_level)");
}

Editor<CommandsScheduler::SchedulerFixture>::Shared
PostgresCrud<CommandsScheduler::SchedulerFixture>::parse(const QSqlRecord& record) const {
  auto fixture = CommandsScheduler::SchedulerFixtureShared::create();
  fixture->setId(record.value(getIdAlias()).value<ID>());
  fixture->setWorkLevel(record.value(getFieldAlias("work_level")).value<quint8>());
  fixture->setStandbyLevel(record.value(getFieldAlias("standby_level")).value<quint8>());
  fixture->setSpeedUp(record.value(getFieldAlias("speed_zero_to_full")).value<quint8>());
  fixture->setSpeedDown(record.value(getFieldAlias("speed_full_to_zero")).value<quint8>());

  return fixture;
}

BindParamsType PostgresCrud<CommandsScheduler::SchedulerFixture>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_geograph", filters.value("geographId")},
      {":id_owner", filters.value("ownerId")},
      {":id_fixture_type", filters.value("fixtureTypeId")},
      {":id_substation", filters.value("substationId")},
      {":id_mode", filters.value("modeId")},
      {":id_contract", filters.value("contractId")},
      {":id_node", filters.value("nodeId")},
  };
}

BindParamsType PostgresCrud<CommandsScheduler::SchedulerFixture>::getInsertParams(const Editor::Shared& fixture) const {
  Q_UNUSED(fixture)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<CommandsScheduler::SchedulerFixture>::getUpdateParams(const Editor::Shared& fixture) const {
  return BindParamsType{
      {":id_fixture", fixture->getId()},
      {":speed_full_to_zero", fixture->getSpeedDown()},
      {":speed_zero_to_full", fixture->getSpeedUp()},
      {":standby_level", fixture->getStandbyLevel()},
      {":work_level", fixture->getWorkLevel()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
