#include "PostgresCrudRoleinclud.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> objFields {
    {"id_role_includ", "id_role_includ", true},
    {"id_role", "id_role_roleright", false},
    {"id_user", "id_user_roleright", false},
    };

PostgresCrud<Roleinclud>::PostgresCrud() {
  setFields(objFields);

  setInsertSql("select user_pkg_i.ins_user_in_role(:id_role, :id_user)");
  setDeleteSql("select user_pkg_i.del_user_from_role(:id)");
}

Reader<Roleinclud>::Shared PostgresCrud<Roleinclud>::parse(const QSqlRecord& record) const {
  auto roleinclud = RoleincludShared::create();
  roleinclud->setId(record.value(getFieldAlias("id_role_includ")).value<ID>());
  roleinclud->setRoleId(record.value(getFieldAlias("id_role")).value<ID>());
  roleinclud->setUserId(record.value(getFieldAlias("id_user")).value<ID>());
  return roleinclud;
}

BindParamsType PostgresCrud<Roleinclud>::getInsertParams(const Editor::Shared &roleinclud) const
{
  return BindParamsType{
      {":id_role", roleinclud->getRoleId()},
      {":id_user", roleinclud->getUserId()}
      };
}

BindParamsType PostgresCrud<Roleinclud>::getUpdateParams(const Editor::Shared &object) const
{
  return BindParamsType();
}

} // namespace PostgresqlGateway
} // namespace light

