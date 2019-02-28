#include "PostgresDeviceCommandGateway.h"

#include "FixtureSwitchOnDeviceCommand.h"
#include "SpeedToLightBaseDeviceCommand.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace light {
namespace PostgresqlGateway {
AbstractDeviceCommandSharedList PostgresDeviceCommandGateway::selectDeviceInCommandsInQueue(const QDateTime& dateTime) {
  AbstractDeviceCommandSharedList result;
  result << getDeviceLightLevelCommandsByDateTime(dateTime);
  result << getDeviceLightSpeedCommandsByDateTime(dateTime);
  return result;
}

void PostgresDeviceCommandGateway::saveDeviceCommands(const AbstractDeviceCommandSharedList& deviceCommands){
    /// FIXME not implemented
    Q_UNUSED(deviceCommands)}

QDateTime PostgresDeviceCommandGateway::getClosestDeviceCommandDateTime() {
  const QString selectFirstDatiTimeSql = "select start_date_time "
					 "from command_pkg_i.command_allinfo_vw c "
					 "where c.id_command_status = 3 "
					 "order by start_date_time limit 1";
  PostgresqlGateway::SelectQuery query(getDb());
  query.prepare(selectFirstDatiTimeSql);
  query.exec();
  QDateTime firstDateTime;
  auto it = query.begin();
  auto record = *it;
  firstDateTime = record.value(0).toDateTime();
  return firstDateTime;
}

AbstractDeviceCommandSharedList
PostgresDeviceCommandGateway::getDeviceLightLevelCommandsByDateTime(const QDateTime& dateTime) const {
  const QString sql =
      "select cs.start_date_time, f.id_gateway, f.num_node, 1 deviceNumber, cs.id_command, "
      "	      cs.work_level, cs.standby_level "
      "from command_switchon_pkg_i.command_switchon_allinfo_vw cs join fixture_pkg_i.fixture_allinfo_vw f "
      "on(cs.id_fixture = f.id_fixture) "
      "where cs.id_command_status = 3 and cs.start_date_time = :start_date_time";

  BindParamsType bindParams{
      {":start_date_time", dateTime},
  };
  auto commands = selectSwitchOnBase(sql, bindParams);

  AbstractDeviceCommandSharedList result;
  std::transform(commands.begin(),
		 commands.end(),
		 std::back_inserter(result),
		 [](FixtureSwitchOnDeviceCommandShared c) { return c.dynamicCast<AbstractDeviceCommand>(); });

  return result;
}

AbstractDeviceCommandSharedList
PostgresDeviceCommandGateway::getDeviceLightSpeedCommandsByDateTime(const QDateTime& dateTime) const {
  const QString sql =
      "select csm.id_command_type, csm.start_date_time, f.id_gateway, f.num_node, 1 deviceNumber, csm.id_command, "
      "csm.speed "
      "from command_speed_mode_pkg_i.command_speed_mode_allinfo_vw csm join fixture_pkg_i.fixture_allinfo_vw f "
      "on(csm.id_fixture = f.id_fixture) "
      "where csm.id_command_status = 3 and csm.start_date_time = :start_date_time";

  BindParamsType bindParams{
      {":start_date_time", dateTime},
  };
  auto commands = selectSpeednBase(sql, bindParams);

  AbstractDeviceCommandSharedList result;
  std::transform(commands.begin(),
		 commands.end(),
		 std::back_inserter(result),
		 [](SpeedToLightBaseDeviceCommandShared c) { return c.dynamicCast<AbstractDeviceCommand>(); });

  return result;
}

FixtureSwitchOnDeviceCommandSharedList
PostgresDeviceCommandGateway::selectSwitchOnBase(const QString& sql, const BindParamsType& params) const {
  auto parser = std::bind(&PostgresDeviceCommandGateway::parseSwitchOnCommand, this, std::placeholders::_1);
  return select<FixtureSwitchOnDeviceCommandSharedList>(sql, params, parser);
}

SpeedToLightBaseDeviceCommandSharedList
PostgresDeviceCommandGateway::selectSpeednBase(const QString& sql, const BindParamsType& params) const {
  auto parser = std::bind(&PostgresDeviceCommandGateway::parseSpeedCommand, this, std::placeholders::_1);
  return select<SpeedToLightBaseDeviceCommandSharedList>(sql, params, parser);
}

FixtureSwitchOnDeviceCommandShared PostgresDeviceCommandGateway::parseSwitchOnCommand(const QSqlRecord& record) const {
  auto fixtureSwitchonCommand = FixtureSwitchOnDeviceCommandShared::create();
  fixtureSwitchonCommand->setDateTime(record.value(0).toDateTime());
  fixtureSwitchonCommand->setGatewayId(record.value(1).value<ulong>());
  fixtureSwitchonCommand->setFirstNode(record.value(2).value<quint8>());
  fixtureSwitchonCommand->setLastNode(record.value(2).value<quint8>());
  fixtureSwitchonCommand->setDeviceNumber(record.value(3).value<quint8>());
  fixtureSwitchonCommand->setCommandId(record.value(4).value<ID>());
  fixtureSwitchonCommand->setWorkLevel(record.value(5).value<quint8>());
  fixtureSwitchonCommand->setStandbyLevel(record.value(6).value<quint8>());
  return fixtureSwitchonCommand;
}

SpeedToLightBaseDeviceCommandShared PostgresDeviceCommandGateway::parseSpeedCommand(const QSqlRecord& record) const {
  auto fixtureLightSpeedCommand = SpeedToLightBaseDeviceCommandShared::create();
  ID commandTypeId = record.value(0).value<ID>();
  auto commandNumber = commandTypeId == 4 ? CommandNumber::SpeedToLightUp : CommandNumber::SpeedToLightDown;
  fixtureLightSpeedCommand->setDateTime(record.value(1).toDateTime());
  fixtureLightSpeedCommand->setCommandNumber(commandNumber);
  fixtureLightSpeedCommand->setGatewayId(record.value(2).value<ulong>());
  fixtureLightSpeedCommand->setFirstNode(record.value(3).value<quint8>());
  fixtureLightSpeedCommand->setLastNode(record.value(3).value<quint8>());
  fixtureLightSpeedCommand->setDeviceNumber(record.value(4).value<quint8>());
  fixtureLightSpeedCommand->setCommandId(record.value(5).value<ID>());
  fixtureLightSpeedCommand->setSpeed(record.value(6).value<quint8>());
  return fixtureLightSpeedCommand;
}

} // namespace PostgresqlGateway
} // namespace light
