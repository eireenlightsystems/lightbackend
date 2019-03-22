#include "FixtureSwitchOnDeviceCommandPostgresCrud.h"

#include "CommandsSchedulerTypeDefs.h"
#include "NotImplementedException.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureSwitchOnDeviceCommandFields{
    {"id_command", "id_command", true},
    {"start_date_time", "start_date_time", false},
    {"work_level", "work_level", false},
    {"standby_level", "standby_level", false},
    {"id_fixture", "id_fixture", false},
    {"id_gateway", "id_gateway", false},
    {"num_node", "num_node", false},
    {"device_number", "device_number", false},
};

PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>::PostgresCrud() {
  setFields(fixtureSwitchOnDeviceCommandFields);
  setView("command_switchon_pkg_i.device_command_switchon_allinfo_vw");
  setUpdateSql("select command_switchon_pkg_i.set_command_status(:id_command, :id_command_status)");
}

Editor<CommandsScheduler::FixtureSwitchOnDeviceCommand>::Shared
PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>::parse(const QSqlRecord& record) const {
  auto fixtureSwitchonCommand = CommandsScheduler::FixtureSwitchOnDeviceCommandShared::create();
  fixtureSwitchonCommand->setId(record.value(getIdAlias()).value<ID>());
  fixtureSwitchonCommand->setDateTime(record.value(getFieldAlias("start_date_time")).toDateTime());
  fixtureSwitchonCommand->setGatewayId(record.value(getFieldAlias("id_gateway")).value<ulong>());
  fixtureSwitchonCommand->setFirstNode(record.value(getFieldAlias("num_node")).value<quint8>());
  fixtureSwitchonCommand->setLastNode(fixtureSwitchonCommand->getFirstNode());
  fixtureSwitchonCommand->setDeviceNumber(record.value(getFieldAlias("device_number")).value<quint8>());
  fixtureSwitchonCommand->setWorkLevel(record.value(getFieldAlias("work_level")).value<quint8>());
  fixtureSwitchonCommand->setStandbyLevel(record.value(getFieldAlias("standby_level")).value<quint8>());
  return fixtureSwitchonCommand;
}

BindParamsType
PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_command_status", CommandStatus::InQueue},
      {":start_date_time", filters.value("dateTime")},
  };
}

BindParamsType
PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>::getInsertParams(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType
PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>::getUpdateParams(const Editor::Shared& command) const {
  return BindParamsType{
      {":id_command", command->getId()},
      {":id_command_status", command->getStatus()},
  };
}

QString PostgresCrud<CommandsScheduler::FixtureSwitchOnDeviceCommand>::getSelectSql() const {
  return QString(
	     "select %1 from %2 where id_command_status = :id_command_status and start_date_time <= :start_date_time")
      .arg(getSelectItems(), getView());
}

} // namespace PostgresqlGateway
} // namespace light
