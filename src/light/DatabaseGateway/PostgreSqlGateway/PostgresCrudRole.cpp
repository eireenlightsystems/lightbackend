#include "PostgresCrudRole.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> objectFields {
    {"id_role", "id_role", true},
    {"name", "name_role", false},
    {"comments", "comments_role", false},
    };

PostgresCrud<Role>::PostgresCrud() {
  setFields(objectFields);
  setView("role_pkg_i.role_vwf()");
  setInsertSql("select role_pkg_i.save(:action, :id_role, :name, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select role_pkg_i.del(:id)");
}

Reader<Role>::Shared PostgresCrud<Role>::parse(const QSqlRecord& record) const {
  auto role = RoleShared::create();
  role->setId(record.value(getFieldAlias("id_role")).value<ID>());
  role->setName(record.value(getFieldAlias("name")).toString());
  role->setComments(record.value(getFieldAlias("comments")).toString());
  return role;
}

BindParamsType PostgresCrud<Role>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<Role>::getInsertParams(const Editor::Shared &role) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_role", QVariant()},
      {":name", role->getName()},
      {":comments", role->getComments()},
      };
}

BindParamsType PostgresCrud<Role>::getUpdateParams(const Editor::Shared &role) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_role", role->getId()},
      {":name", role->getName()},
      {":comments", role->getComments()},
      };
}

} // namespace PostgresqlGateway
} // namespace light


