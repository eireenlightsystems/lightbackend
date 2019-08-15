#include "PostgresCrudUser.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> userFields {
    {"id_user", "id_user", true},
    {"id_contragent", "id_contragent_user", false},
    {"login", "login_user", false},
    {"code", "code_user", false},
    {"name", "name_user", false},
    {"inn", "inn_user", false},
    {"adres", "adres_user", false},
    {"comments", "comments_user", false},
};

PostgresCrud<User>::PostgresCrud() {
  setFields(userFields);
  setView("user_pkg_i.user_vwf()");
  setInsertSql("select user_pkg_i.save(:action, :id_user, :id_contragent, :login, :password, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select user_pkg_i.del(:id)");
}

Reader<User>::Shared PostgresCrud<User>::parse(const QSqlRecord& record) const {
  auto user = UserShared::create();
  user->setId(record.value(getFieldAlias("id_user")).value<ID>());
  user->setContragentId(record.value(getFieldAlias("id_contragent")).value<ID>());
  user->setLogin(record.value(getFieldAlias("login")).toString());
  user->setContragentCode(record.value(getFieldAlias("code")).toString());
  user->setContragentName(record.value(getFieldAlias("name")).toString());
  user->setContragentInn(record.value(getFieldAlias("inn")).toString());
  user->setContragentAdres(record.value(getFieldAlias("adres")).toString());
  user->setComments(record.value(getFieldAlias("comments")).toString());
  return user;
}

BindParamsType PostgresCrud<User>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<User>::getInsertParams(const Editor::Shared &user) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_user", QVariant()},
      {":id_contragent", user->getContragentId()},
      {":login", user->getLogin()},
      {":password", user->getPassword()},
      {":comments", user->getComments()},
      };
}

BindParamsType PostgresCrud<User>::getUpdateParams(const Editor::Shared &user) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_user", user->getId()},
      {":id_contragent", user->getContragentId()},
      {":login", user->getLogin()},
      {":password", user->getPassword()},
      {":comments", user->getComments()},
      };
}

} // namespace PostgresqlGateway
} // namespace light

