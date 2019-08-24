#include "PostgresCrudRoleright.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> objFields {
    {"id_roleright", "id_roleright", true},
    {"id_component", "id_component_roleright", false},
    {"code_component", "code_component_roleright", false},
    {"name_component", "name_component_roleright", false},
    {"comments_component", "comments_component_roleright", false},
    {"id_role", "id_role_roleright", false},
    {"name_role", "name_role_roleright", false},
    {"rights", "rights_roleright", false},
    };

PostgresCrud<Roleright>::PostgresCrud() {
  setFields(objFields);
  setView("roleright_pkg_i.roleright_vwf(:id_role)");
  setInsertSql("select roleright_pkg_i.save(:action, :id_roleright, :id_role, :code_component)");
  setDeleteSql("select roleright_pkg_i.del(:id)");
}

Reader<Roleright>::Shared PostgresCrud<Roleright>::parse(const QSqlRecord& record) const {
  auto roleright = RolerightShared::create();
  roleright->setId(record.value(getFieldAlias("id_roleright")).value<ID>());
  roleright->setComponentId(record.value(getFieldAlias("id_component")).value<ID>());
  roleright->setComponentCode(record.value(getFieldAlias("code_component")).toString());
  roleright->setComponentName(record.value(getFieldAlias("name_component")).toString());
  roleright->setComponentComments(record.value(getFieldAlias("comments_component")).toString());
  roleright->setRoleId(record.value(getFieldAlias("id_role")).value<ID>());
  roleright->setRoleName(record.value(getFieldAlias("name_role")).toString());
  roleright->setRights(record.value(getFieldAlias("rights")).toString());
  return roleright;
}

BindParamsType PostgresCrud<Roleright>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{
      {":id_role", filters.value("roleId")}
  };
}

BindParamsType PostgresCrud<Roleright>::getInsertParams(const Editor::Shared &roleright) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_roleright", QVariant()},
      {":id_role", roleright->getRoleId()},
      {":code_component", roleright->getComponentCode()},
      };
}

BindParamsType PostgresCrud<Roleright>::getUpdateParams(const Editor::Shared &object) const
{
  return BindParamsType();
}

} // namespace PostgresqlGateway
} // namespace light
