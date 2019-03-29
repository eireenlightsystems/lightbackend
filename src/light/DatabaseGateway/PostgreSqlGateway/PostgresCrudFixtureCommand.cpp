#include "PostgresCrudFixtureCommand.h"

#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "NotImplementedException.h"

namespace light {
namespace PostgresqlGateway {

PostgresCrud<FixtureCommand>::PostgresCrud() {
  setDeleteSql("select fixture_command_pkg_i.del(:id)");
}

Editor<FixtureCommand>::Shared PostgresCrud<FixtureCommand>::selById(ID id) const {
  Q_UNUSED(id)
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::SharedList PostgresCrud<FixtureCommand>::sel() const {
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::SharedList PostgresCrud<FixtureCommand>::sel(const IDList& ids) const {
  Q_UNUSED(ids)
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::SharedList PostgresCrud<FixtureCommand>::sel(const QVariantHash& filters) const {
  Q_UNUSED(filters)
  throw NotImplementedException(Q_FUNC_INFO);
}

void PostgresCrud<FixtureCommand>::save(const Editor::SharedList& objects) const {
  Q_UNUSED(objects)
  throw NotImplementedException(Q_FUNC_INFO);
}

void PostgresCrud<FixtureCommand>::save(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::Shared PostgresCrud<FixtureCommand>::parse(const QSqlRecord& record) const {
  Q_UNUSED(record)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<FixtureCommand>::getSelectParams(const QVariantHash& filters) const {
  Q_UNUSED(filters)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<FixtureCommand>::getInsertParams(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<FixtureCommand>::getUpdateParams(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

const QList<Field> fixtureCommandTypeFields{
    {"id_command_type", "id_command_type", true},
    {"name_command_type", "name_command_type", false},
};

PostgresCrud<FixtureCommandType>::PostgresCrud() {
  setFields(fixtureCommandTypeFields);
  setView("command_pkg_i.command_type_vw");
}

Reader<FixtureCommandType>::Shared PostgresCrud<FixtureCommandType>::parse(const QSqlRecord& record) const {
  auto fixtureCommandType = FixtureCommandTypeShared::create();
  fixtureCommandType->setId(record.value(getIdAlias()).value<ID>());
  fixtureCommandType->setName(record.value(getFieldAlias("name_command_type")).toString());
  return fixtureCommandType;
}

const QList<Field> fixtureLightLevelCommandTypeFields{
    {"id_command_type", "id_command_type", true},
    {"name_command_type", "name_command_type", false},
};

PostgresCrud<FixtureLightLevelCommandType>::PostgresCrud() {
  setFields(fixtureLightLevelCommandTypeFields);
  setView("command_switchon_pkg_i.command_type_vw");
}

Reader<FixtureLightLevelCommandType>::Shared
PostgresCrud<FixtureLightLevelCommandType>::parse(const QSqlRecord& record) const {
  PostgresCrud<FixtureCommandType> commandTypeCrud;
  auto commandType = commandTypeCrud.parse(record);
  auto lightLevelCommandType = FixtureLightLevelCommandTypeShared::create(*commandType);
  return lightLevelCommandType;
}

const QList<Field> fixtureLightSpeedCommandTypeFields{
    {"id_command_type", "id_command_type", true},
    {"name_command_type", "name_command_type", false},
};

PostgresCrud<FixtureLightSpeedCommandType>::PostgresCrud() {
  setFields(fixtureLightLevelCommandTypeFields);
  setView("command_speed_mode_pkg_i.command_type_vw");
}

Reader<FixtureLightSpeedCommandType>::Shared
PostgresCrud<FixtureLightSpeedCommandType>::parse(const QSqlRecord& record) const {
  PostgresCrud<FixtureCommandType> commandTypeCrud;
  auto commandType = commandTypeCrud.parse(record);
  auto lightSpeedCommandType = FixtureLightSpeedCommandTypeShared::create(*commandType);
  return lightSpeedCommandType;
}

const QList<Field> fixtureCommandStatusFields{
    {"id_command_status", "id_command_status", true},
    {"code_command_status", "code_command_status", false},
    {"name_command_status", "name_command_status", false},
};

PostgresCrud<FixtureCommandStatus>::PostgresCrud() {
  setFields(fixtureCommandStatusFields);
  setView("command_pkg_i.command_status_vw");
}

Reader<FixtureCommandStatus>::Shared PostgresCrud<FixtureCommandStatus>::parse(const QSqlRecord& record) const {
  auto fixtureCommandStatus = FixtureCommandStatusShared::create();
  fixtureCommandStatus->setId(record.value(getIdAlias()).value<ID>());
  fixtureCommandStatus->setCode(record.value(getFieldAlias("code_command_status")).toString());
  fixtureCommandStatus->setName(record.value(getFieldAlias("name_command_status")).toString());
  return fixtureCommandStatus;
}

} // namespace PostgresqlGateway
} // namespace light
