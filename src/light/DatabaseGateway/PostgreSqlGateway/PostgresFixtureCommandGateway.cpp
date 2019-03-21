#include "PostgresFixtureCommandGateway.h"

#include "DeleteQuery.h"
#include "FixtureCommand.h"
#include "typedefs.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace light {
namespace PostgresqlGateway {
PostgresFixtureCommandGateway::PostgresFixtureCommandGateway() {
}

FixtureCommandShared PostgresFixtureCommandGateway::selectCommand(ID id) {
  auto commands = selectCommands({id});
  if (commands.count()) {
    return commands.first();
  }

  return FixtureCommandShared();
}

FixtureCommandSharedList PostgresFixtureCommandGateway::selectCommands(const QList<ID>& ids) {
  FixtureCommandSharedList result;
  const QString sql = "select c.id_command, c.id_command_status, c.id_fixture, c.start_date_time "
		      "from command_pkg_i.command_allinfo_vw c "
		      "where c.id_command = :id_command ";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_command", id},
    };
    result << selectBase(sql, bindParams);
  }
  return result;
}

void PostgresFixtureCommandGateway::deleteCommand(const FixtureCommandShared& command) {
  deleteCommands({command});
}

void PostgresFixtureCommandGateway::deleteCommands(const FixtureCommandSharedList& commands) {
  const QString deleteFromComandSql = "select command_pkg_i.del(:id_command)";
  QVariantList bindIds;
  std::transform(commands.begin(), commands.end(), std::back_inserter(bindIds), [](const FixtureCommandShared c) {
    return QVariant(c->getId());
  });
  BindParamsType bindParams{
      {":id_command", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteFromComandSql, bindParams);
}

FixtureCommandSharedList PostgresFixtureCommandGateway::selectBase(const QString& sql,
								   const BindParamsType& params) const {
  auto parser = std::bind(&PostgresFixtureCommandGateway::parseFixtureCommand, this, std::placeholders::_1);
  return select<FixtureCommandSharedList>(sql, params, parser);
}

FixtureCommandShared PostgresFixtureCommandGateway::parseFixtureCommand(const QSqlRecord& record) const {
  auto fixtureLightLevelCommand = FixtureCommandShared::create();
  fixtureLightLevelCommand->setId(record.value(0).value<ID>());
  fixtureLightLevelCommand->setStatus(record.value(1).value<CommandStatus>());
  fixtureLightLevelCommand->setFixtureId(record.value(2).value<ID>());
  fixtureLightLevelCommand->setStartDateTime(record.value(3).toDateTime());

  return fixtureLightLevelCommand;
}
} // namespace PostgresqlGateway
} // namespace light
