#include "PostgresCrudFixtureLightLevelCommand.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureLightLevelCommandFields{
    {"id_command", "id_command", true},
    {"start_date_time", "start_date_time", false},
    {"work_level", "work_level", false},
    {"standby_level", "standby_level", false},

    {"id_command_type", "id_command_type", false},
//    {"code_command_type", "code_command_type", false},
//    {"name_command_type", "name_command_type", false},

    {"id_command_status", "id_command_status", false},
//    {"code_command_status", "code_command_status", false},
//    {"name_command_status", "name_command_status", false},

    {"id_fixture", "id_fixture", false},
};

PostgresCrud<FixtureLightLevelCommand>::PostgresCrud() {
  setFields(fixtureLightLevelCommandFields);
  setView("command_switchon_pkg_i.command_switchon_vwf(:id_command_type, :id_command_status, :id_fixture, "
	  ":start_datetime, :end_datetime)");
  setInsertSql("select command_switchon_pkg_i.ins(:id_command_type, :id_command_status, :id_fixture, :start_datetime, "
	       ":work_level, :standby_level)");
  setUpdateSql("select command_switchon_pkg_i.upd(:id_command, :id_command_type, :id_command_status, :id_fixture, "
	       ":start_datetime, :work_level, :standby_level)");
  setDeleteSql("select command_switchon_pkg_i.del(:id)");
}

Editor<FixtureLightLevelCommand>::Shared PostgresCrud<FixtureLightLevelCommand>::parse(const QSqlRecord& record) const {
  auto fixtureLightLevelCommand = FixtureLightLevelCommandShared::create();
  fixtureLightLevelCommand->setId(record.value(getIdAlias()).value<ID>());
  fixtureLightLevelCommand->setStatus(record.value(getFieldAlias("id_command_status")).value<CommandStatus>());
  fixtureLightLevelCommand->setFixtureId(record.value(getFieldAlias("id_fixture")).value<ID>());
  fixtureLightLevelCommand->setStartDateTime(record.value(getFieldAlias("start_date_time")).toDateTime());
  fixtureLightLevelCommand->setWorkLevel(record.value(getFieldAlias("work_level")).value<quint8>());
  fixtureLightLevelCommand->setStandbyLevel(record.value(getFieldAlias("standby_level")).value<quint8>());
  return fixtureLightLevelCommand;
}

BindParamsType PostgresCrud<FixtureLightLevelCommand>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_fixture", filters.value("fixtureId")},
      {":id_command_status", filters.value("statusId")},
      {":start_datetime", filters.value("startDateTime")},
      {":end_datetime", filters.value("endDateTime")},
  };
}

BindParamsType PostgresCrud<FixtureLightLevelCommand>::getInsertParams(const Editor::Shared& command) const {
  return BindParamsType{
      {":id_command_type", 2},
      {":id_command_status", 3},
      {":id_fixture", command->getFixtureId()},
      {":start_datetime", command->getStartDateTime()},
      {":work_level", command->getWorkLevel()},
      {":standby_level", command->getStandbyLevel()},
  };
}

BindParamsType PostgresCrud<FixtureLightLevelCommand>::getUpdateParams(const Editor::Shared& command) const {
  return BindParamsType{
      {":id_command", command->getId()},
      {":id_command_type", 2},
      {":id_command_status", command->getStatus()},
      {":id_fixture", command->getFixtureId()},
      {":start_date_time", command->getStartDateTime()},
      {":work_level", command->getWorkLevel()},
      {":standby_level", command->getStandbyLevel()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
