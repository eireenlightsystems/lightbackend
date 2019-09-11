#include "PostgresCrudComponent.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> componentFields {
    {"id_component", "id_component", true},
    {"code", "code_component", false},
    {"name", "name_component", false},
    {"comments", "comments_component", false},
    {"rights", "rights_component", false},
    };

PostgresCrud<Component>::PostgresCrud() {
  setFields(componentFields);
  setView("component_pkg_i.component_vwf(:id_role, :id_user)");
  setInsertSql("select component_pkg_i.save(:action, :id_component, :code, :name, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select component_pkg_i.del(:id)");
}

Reader<Component>::Shared PostgresCrud<Component>::parse(const QSqlRecord& record) const {
  auto component = ComponentShared::create();
  component->setId(record.value(getFieldAlias("id_component")).value<ID>());
  component->setCode(record.value(getFieldAlias("code")).toString());
  component->setName(record.value(getFieldAlias("name")).toString());
  component->setComments(record.value(getFieldAlias("comments")).toString());
  component->setRights(record.value(getFieldAlias("rights")).toString());
  return component;
}

BindParamsType PostgresCrud<Component>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{
      {":id_role", filters.value("roleId")},
      {":id_user", filters.value("userId")}
  };
}

BindParamsType PostgresCrud<Component>::getInsertParams(const Editor::Shared &component) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_component", QVariant()},
      {":code", component->getCode()},
      {":name", component->getName()},
      {":comments", component->getComments()},
      };
}

BindParamsType PostgresCrud<Component>::getUpdateParams(const Editor::Shared &component) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_component", component->getId()},
      {":code", component->getCode()},
      {":name", component->getName()},
      {":comments", component->getComments()},
      };
}

} // namespace PostgresqlGateway
} // namespace light



