#include "PostgresFixtureLightSpeedCommandGateway.h"

#include "DeleteQuery.h"
#include "FixtureLightSpeedCommand.h"
#include "InsertQuery.h"
#include "QueryBuilder.h"
#include "SelectQuery.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace light {
namespace PostgresqlGateway {
FixtureLightSpeedCommandShared PostgresFixtureLightSpeedCommandGateway::selectLightSpeedCommand(ID id) {
  auto commands = selectLightSpeedCommands({id});
  if (commands.count()) {
    commands.first();
  }

  return FixtureLightSpeedCommandShared();
}

FixtureLightSpeedCommandSharedList
PostgresFixtureLightSpeedCommandGateway::selectLightSpeedCommands(const QList<ID>& ids) {
  FixtureLightSpeedCommandSharedList result;
  const QString sql = "select id_command, id_command_status, id_fixture, start_date_time, id_command_type, speed "
		      "from command_speed_mode_pkg_i.command_speed_mode_allinfo_vw "
		      "where id_fixture = :id_fixture";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_command", id},
    };
    result << selectBase(sql, bindParams);
  }
  return result;
}

FixtureLightSpeedCommandSharedList
PostgresFixtureLightSpeedCommandGateway::selectLightSpeedCommands(const QDateTime& dateTime) {
  FixtureLightSpeedCommandSharedList result;
  const QString sql = "select id_command, id_command_status, id_fixture, start_date_time, id_command_type, speed "
		      "from command_speed_mode_pkg_i.command_speed_mode_allinfo_vw "
		      "where start_date_time =  :start_date_time";
  const BindParamsType bindParams{
      {":start_date_time", dateTime},
  };
  return selectBase(sql, bindParams);
}

FixtureLightSpeedCommandSharedList
PostgresFixtureLightSpeedCommandGateway::selectLightSpeedCommands(const FixtureCommandsFilter& filter) {
  FixtureLightSpeedCommandSharedList result;
  const QString sql =
      "select id_command, id_command_status, id_fixture, start_date_time, id_command_type, speed "
      "from command_speed_mode_pkg_i.command_speed_mode_allinfo_vw "
      "where id_fixture = :id_fixture and id_command_status = coalesce(:id_command_status, id_command_status) and "
      "start_date_time between :from and :to";

  BindParamsType bindParams{
      {":id_fixture", filter.fixtureId},
      {":id_command_status", filter.status == CommandStatus::None ? QVariant() : filter.status},
      {":from", filter.from},
      {":to", filter.to},
  };
  return selectBase(sql, bindParams);
}

void PostgresFixtureLightSpeedCommandGateway::saveLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  saveLightSpeedCommands({command});
}

void PostgresFixtureLightSpeedCommandGateway::saveLightSpeedCommands(
    const FixtureLightSpeedCommandSharedList& commands) {
  getDb().transaction();

  for (const auto& c : commands) {
    if (c->getCommandId()) {
      updateLightSpeedCommand(c);
    } else {
      insertLightSpeedCommand(c);
    }
  }
  getDb().commit();
}

void PostgresFixtureLightSpeedCommandGateway::deleteLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  deleteLightSpeedCommands({command});
}

void PostgresFixtureLightSpeedCommandGateway::deleteLightSpeedCommands(
    const FixtureLightSpeedCommandSharedList& commands) {
  const QString deleteFromCommandSql = "select command_speed_mode_pkg_i.del(:id_command)";
  QVariantList bindIds;
  std::transform(commands.begin(),
		 commands.end(),
		 std::back_inserter(bindIds),
		 [](FixtureLightSpeedCommandShared command) { return QVariant(command->getCommandId()); });
  BindParamsType bindParams{
      {":id_command", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteFromCommandSql, bindParams);
}

FixtureLightSpeedCommandSharedList
PostgresFixtureLightSpeedCommandGateway::selectBase(const QString& sql, const BindParamsType &params) const {
  auto parser =
      std::bind(&PostgresFixtureLightSpeedCommandGateway::parseLightSpeedCommand, this, std::placeholders::_1);
  return select<FixtureLightSpeedCommandSharedList>(sql, params, parser);
}

FixtureLightSpeedCommandShared
PostgresFixtureLightSpeedCommandGateway::parseLightSpeedCommand(const QSqlRecord& record) const {
  auto fixtureLightSpeedCommand = FixtureLightSpeedCommandShared::create();
  fixtureLightSpeedCommand->setCommandId(record.value(0).value<ID>());
  fixtureLightSpeedCommand->setStatus(record.value(1).value<CommandStatus>());
  fixtureLightSpeedCommand->setFixtureId(record.value(2).value<ID>());
  fixtureLightSpeedCommand->setStartDateTime(record.value(3).toDateTime());

  auto commandTypeId = record.value(4).value<ID>();
  auto directionType = commandTypeId == 4 ? FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork
					  : FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::WorkToStandby;
  fixtureLightSpeedCommand->setDirectionType(directionType);
  fixtureLightSpeedCommand->setSpeed(record.value(5).value<quint8>());
  return fixtureLightSpeedCommand;
}

void PostgresFixtureLightSpeedCommandGateway::insertLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  const QString sql = "select command_speed_mode_pkg_i.ins(:id_command_type, :id_command_status, "
		      ":id_fixture, :start_date_time, :speed)";
  ID commandTypeId =
      command->getDirectionType() == FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork ? 4 : 5;
  BindParamsType bindParams{
      {":id_command_type", commandTypeId},
      {":id_command_status", 3},
      {":id_fixture", command->getFixtureId()},
      {":start_date_time", command->getStartDateTime()},
      {":speed", command->getSpeed()},
  };
  auto query = buildAndExecQuery<InsertQuery>(sql, bindParams);
}

void PostgresFixtureLightSpeedCommandGateway::updateLightSpeedCommand(const FixtureLightSpeedCommandShared& command) {
  const QString sql = "select command_speed_mode_pkg_i.upd(:id_command, :id_command_type, :id_command_status, "
		      ":id_fixture, :start_date_time, :speed)";
  ID commandTypeId =
      command->getDirectionType() == FixtureLightSpeedCommand::FixtureLightSpeedDirectionType::StandbyToWork ? 4 : 5;
  BindParamsType bindParams{
      {":id_command", command->getCommandId()},
      {":id_command_type", commandTypeId},
      {":id_command_status", command->getStatus()},
      {":id_fixture", command->getFixtureId()},
      {":start_date_time", command->getStartDateTime()},
      {":speed", command->getSpeed()},
  };
  buildAndExecQuery<UpdateQuery>(sql, bindParams);
}
} // namespace PostgresqlGateway
} // namespace light
