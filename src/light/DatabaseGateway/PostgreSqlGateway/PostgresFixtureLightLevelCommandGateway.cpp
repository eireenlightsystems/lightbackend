#include "PostgresFixtureLightLevelCommandGateway.h"

#include "DeleteQuery.h"
#include "FixtureLightLevelCommand.h"
#include "InsertQuery.h"
#include "QueryBuilder.h"
#include "SelectQuery.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <functional>

namespace light {
namespace PostgresqlGateway {
FixtureLightLevelCommandShared PostgresFixtureLightLevelCommandGateway::selectLightLevelCommand(ID id) {
  auto commands = selectLightLevelCommands({id});
  if (commands.count()) {
    commands.first();
  }

  return FixtureLightLevelCommandShared();
}

FixtureLightLevelCommandSharedList
PostgresFixtureLightLevelCommandGateway::selectLightLevelCommands(const QList<ID>& ids) {
  FixtureLightLevelCommandSharedList result;
  const QString sql =
      "select id_command, id_command_status, id_fixture, start_date_time, work_level, cstandby_level "
      "from command_switchon_pkg_i.command_switchon_allinfo_vw "
      "where id_command = :id_command";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_command", id},
    };
    result << selectBase(sql, bindParams);
  }
  return result;
}

FixtureLightLevelCommandSharedList
PostgresFixtureLightLevelCommandGateway::selectLightLevelCommands(const QDateTime& dateTime) {
  FixtureLightLevelCommandSharedList result;
  const QString selectComandSwitchonSql =
      "select id_command, id_command_status, id_fixture, start_date_time, work_level, standby_level "
      "from command_switchon_pkg_i.command_switchon_allinfo_vw "
      "where start_date_time = :start_date_time";
  const BindParamsType bindParams{
      {":start_date_time", dateTime},
  };
  return selectBase(selectComandSwitchonSql, bindParams);
}

FixtureLightLevelCommandSharedList
PostgresFixtureLightLevelCommandGateway::selectLightLevelCommands(const FixtureCommandsFilter& filter) {
  const QString selectComandSwitchonSql =
      "select id_command, id_command_status, id_fixture, start_date_time, work_level, standby_level "
      "from command_switchon_pkg_i.command_switchon_allinfo_vw "
      "where id_fixture = :id_fixture and id_command_status = coalesce(:id_command_status, id_command_status) "
      "and start_date_time between :from and :to";

  BindParamsType bindParams{
      {":id_fixture", filter.fixtureId},
      {":id_command_status", filter.status == CommandStatus::None ? QVariant() : filter.status},
      {":from", filter.from},
      {":to", filter.to},
  };
  return selectBase(selectComandSwitchonSql, bindParams);
}

void PostgresFixtureLightLevelCommandGateway::saveLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  saveLightLevelCommands(FixtureLightLevelCommandSharedList{command});
}

void PostgresFixtureLightLevelCommandGateway::saveLightLevelCommands(
    const FixtureLightLevelCommandSharedList& commands) {
  getDb().transaction();
  for (auto command : commands) {
    if (command->getId()) {
      updateLightLevelCommand(command);
    } else {
      insertLightLevelCommand(command);
    }
  }
  getDb().commit();
}

void PostgresFixtureLightLevelCommandGateway::deleteLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  deleteLightLevelCommands(FixtureLightLevelCommandSharedList{command});
}

void PostgresFixtureLightLevelCommandGateway::deleteLightLevelCommands(
    const FixtureLightLevelCommandSharedList& commands) {
  const QString deleteFromCommandSql = "select command_switchon_pkg_i.del(:id_command)";
  QVariantList bindIds;
  std::transform(commands.begin(),
		 commands.end(),
		 std::back_inserter(bindIds),
		 [](FixtureLightLevelCommandShared command) { return QVariant(command->getId()); });
  BindParamsType bindParams{
      {":id_command", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteFromCommandSql, bindParams);
}

FixtureLightLevelCommandSharedList
PostgresFixtureLightLevelCommandGateway::selectBase(const QString& sql, const BindParamsType& params) const {
  auto parser =
      std::bind(&PostgresFixtureLightLevelCommandGateway::parseLightLevelCommand, this, std::placeholders::_1);
  return select<FixtureLightLevelCommandSharedList>(sql, params, parser);
}

FixtureLightLevelCommandShared
PostgresFixtureLightLevelCommandGateway::parseLightLevelCommand(const QSqlRecord& record) const {
  auto fixtureLightLevelCommand = FixtureLightLevelCommandShared::create();
  fixtureLightLevelCommand->setId(record.value(0).value<ID>());
  fixtureLightLevelCommand->setStatus(record.value(1).value<CommandStatus>());
  fixtureLightLevelCommand->setFixtureId(record.value(2).value<ID>());
  fixtureLightLevelCommand->setStartDateTime(record.value(3).toDateTime());

  fixtureLightLevelCommand->setWorkLevel(record.value(4).value<quint8>());
  fixtureLightLevelCommand->setStandbyLevel(record.value(5).value<quint8>());
  return fixtureLightLevelCommand;
}

void PostgresFixtureLightLevelCommandGateway::insertLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  const QString commandSwitchonInsertSql = "select command_switchon_pkg_i.ins(:id_command_type, :id_command_status, "
					   ":id_fixture, :start_date_time, :work_level, :standby_level)";
  BindParamsType bindParams{
      {":id_command_type", 2},
      {":id_command_status", 3},
      {":id_fixture", command->getFixtureId()},
      {":start_date_time", command->getStartDateTime()},
      {":work_level", command->getWorkLevel()},
      {":standby_level", command->getStandbyLevel()},
  };
  auto query = buildAndExecQuery<InsertQuery>(commandSwitchonInsertSql, bindParams);
}

void PostgresFixtureLightLevelCommandGateway::updateLightLevelCommand(const FixtureLightLevelCommandShared& command) {
  const QString sql = "select command_switchon_pkg_i.upd(:id_command, :id_command_type, :id_command_status, "
		      ":id_fixture, :start_date_time, :work_level, :standby_level)";
  BindParamsType bindParams{
      {":id_command", command->getId()},
      {":id_command_type", 2},
      {":id_command_status", command->getStatus()},
      {":id_fixture", command->getFixtureId()},
      {":start_date_time", command->getStartDateTime()},
      {":work_level", command->getWorkLevel()},
      {":standby_level", command->getStandbyLevel()},
  };
  buildAndExecQuery<UpdateQuery>(sql, bindParams);
}

} // namespace PostgresqlGateway
} // namespace light
