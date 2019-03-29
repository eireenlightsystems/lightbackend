#include "PostgresCrudFixtureLightSpeedCommand.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureLightSpeedCommandFields{
    {"id_command", "id_command", true},
    {"start_date_time", "start_date_time", false},
    {"speed", "speed", false},

    {"id_command_type", "id_command_type", false},
    //    {"code_command_type", "code_command_type", false},
    //    {"name_command_type", "name_command_type", false},

    {"id_command_status", "id_command_status", false},
    //    {"code_command_status", "code_command_status", false},
    //    {"name_command_status", "name_command_status", false},

    {"id_fixture", "id_fixture", false},
};

PostgresCrud<FixtureLightSpeedCommand>::PostgresCrud() {
  setFields(fixtureLightSpeedCommandFields);
  setView("command_speed_mode_pkg_i.command_speed_mode_vwf(:id_command_type, :id_command_status, :id_fixture, "
	  ":start_datetime, :end_datetime)");
  setInsertSql(
      "select command_speed_mode_pkg_i.ins(:id_command_type, :id_command_status, :id_fixture, :start_datetime, "
      ":speed)");
  setUpdateSql("select command_speed_mode_pkg_i.upd(:id_command, :id_command_type, :id_command_status, :id_fixture, "
	       ":speed)");
  setDeleteSql("select command_speed_mode_pkg_i.del(:id)");
}

Editor<FixtureLightSpeedCommand>::Shared PostgresCrud<FixtureLightSpeedCommand>::parse(const QSqlRecord& record) const {
  auto fixtureLightSpeedCommand = FixtureLightSpeedCommandShared::create();
  fixtureLightSpeedCommand->setId(record.value(getIdAlias()).value<ID>());
  auto directionType = FixtureLightSpeedCommand::FixtureLightSpeedDirectionType(
      record.value(getFieldAlias("id_command_type")).toInt());
  fixtureLightSpeedCommand->setDirectionType(directionType);
  fixtureLightSpeedCommand->setStatus(record.value(getFieldAlias("id_command_status")).value<CommandStatus>());
  fixtureLightSpeedCommand->setFixtureId(record.value(getFieldAlias("id_fixture")).value<ID>());
  fixtureLightSpeedCommand->setStartDateTime(record.value(getFieldAlias("start_date_time")).toDateTime());
  fixtureLightSpeedCommand->setSpeed(record.value(getFieldAlias("speed")).value<quint8>());
  return fixtureLightSpeedCommand;
}

BindParamsType PostgresCrud<FixtureLightSpeedCommand>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_fixture", filters.value("fixtureId")},
      {":id_command_type", filters.value("speedDirectionId")},
      {":id_command_status", filters.value("statusId")},
      {":start_datetime", filters.value("startDateTime")},
      {":end_datetime", filters.value("endDateTime")},
  };
}

BindParamsType PostgresCrud<FixtureLightSpeedCommand>::getInsertParams(const Editor::Shared& command) const {
  ID commandTypeId =
      command->getDirectionType() == FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork ? 4 : 5;
  return BindParamsType{
      {":id_command_type", commandTypeId},
      {":id_command_status", 3},
      {":id_fixture", command->getFixtureId()},
      {":start_datetime", command->getStartDateTime()},
      {":speed", command->getSpeed()},
  };
}

BindParamsType PostgresCrud<FixtureLightSpeedCommand>::getUpdateParams(const Editor::Shared& command) const {
  ID commandTypeId =
      command->getDirectionType() == FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork ? 4 : 5;
  return BindParamsType{
      {":id_command", command->getId()},
      {":id_command_type", commandTypeId},
      {":id_command_status", command->getStatus()},
      {":id_fixture", command->getFixtureId()},
      {":start_date_time", command->getStartDateTime()},
      {":speed", command->getSpeed()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
