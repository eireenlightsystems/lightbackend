#include "SpeedToLightBaseDeviceCommandPostgresCrud.h"

#include "NotImplementedException.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> speedToLightBaseDeviceCommandFields{
    {"id_command", "id_command", true},
    {"id_command_type", "id_command_type", false},
    {"start_date_time", "start_date_time", false},
    {"speed", "speed", false},
    {"id_fixture", "id_fixture", false},
    {"id_gateway", "id_gateway", false},
    {"num_node", "num_node", false},
    {"device_number", "device_number", false},
};

PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>::PostgresCrud() {
  setFields(speedToLightBaseDeviceCommandFields);
  setView("command_speed_mode_pkg_i.device_command_speed_mode_vw");
  setUpdateSql("select command_speed_mode_pkg_i.set_command_status(:id_command, :id_command_status)");
}

Editor<CommandsScheduler::SpeedToLightBaseDeviceCommand>::Shared
PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>::parse(const QSqlRecord& record) const {
  auto fixtureLightSpeedCommand = CommandsScheduler::SpeedToLightBaseDeviceCommandShared::create();
  ID commandTypeId = record.value(getFieldAlias("id_command_type")).value<ID>();
  auto commandNumber = commandTypeId == 4 ? CommandsScheduler::CommandNumber::SpeedToLightUp
					  : CommandsScheduler::CommandNumber::SpeedToLightDown;
  fixtureLightSpeedCommand->setId(record.value(getIdAlias()).value<ID>());
  fixtureLightSpeedCommand->setDateTime(record.value(getFieldAlias("start_date_time")).toDateTime());
  fixtureLightSpeedCommand->setCommandNumber(commandNumber);
  fixtureLightSpeedCommand->setGatewayId(record.value(getFieldAlias("id_gateway")).value<ulong>());
  fixtureLightSpeedCommand->setFirstNode(record.value(getFieldAlias("num_node")).value<quint8>());
  fixtureLightSpeedCommand->setLastNode(record.value(fixtureLightSpeedCommand->getFirstNode()).value<quint8>());
  fixtureLightSpeedCommand->setDeviceNumber(record.value(getFieldAlias("device_number")).value<quint8>());
  fixtureLightSpeedCommand->setSpeed(record.value(getFieldAlias("speed")).value<quint8>());
  return fixtureLightSpeedCommand;
}

QString PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>::getSelectSql() const {
  return QString(
	     "select %1 from %2 where id_command_status = :id_command_status and start_date_time <= :start_date_time")
      .arg(getSelectItems(), getView());
}

BindParamsType
PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_command_status", CommandStatus::InQueue},
      {":start_date_time", filters.value("dateTime")},
  };
}

BindParamsType
PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>::getInsertParams(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType
PostgresCrud<CommandsScheduler::SpeedToLightBaseDeviceCommand>::getUpdateParams(const Editor::Shared& command) const {
  return BindParamsType{
      {":id_command", command->getId()},
      {":id_command_status", command->getStatus()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
