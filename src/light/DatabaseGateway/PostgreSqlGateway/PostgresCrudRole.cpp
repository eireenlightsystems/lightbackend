#include "PostgresCrudRole.h"

#include <QDebug>
#include <QSet>
#include <QSqlRecord>
#include <QVariant>
#include "User.h"
#include "PostgresCrudUser.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> objectFields {
    {"id_role", "id_role", true},
    {"id_contragent", "id_contragent_role", false},
    {"contragent_code", "contragent_code_role", false},
    {"contragent_name", "contragent_name_role", false},
    {"contragent_inn", "contragent_inn_role", false},
    {"contragent_adres", "contragent_adres_role", false},
    {"name", "name_role", false},
    {"comments", "comments_role", false},
    };

PostgresCrud<Role>::PostgresCrud() {
  setFields(objectFields);
  setView("role_pkg_i.role_vwf(:id_user, :not_id_user)");
  setInsertSql("select role_pkg_i.save(:action, :id_role, :id_contragent, :name, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select role_pkg_i.del(:id)");
}

Reader<Role>::Shared PostgresCrud<Role>::parse(const QSqlRecord& record) const {
  auto role = RoleShared::create();
  role->setId(record.value(getFieldAlias("id_role")).value<ID>());
  role->setContragentId(record.value(getFieldAlias("id_contragent")).value<ID>());
  role->setContragentCode(record.value(getFieldAlias("contragent_code")).toString());
  role->setContragentName(record.value(getFieldAlias("contragent_name")).toString());
  role->setContragentInn(record.value(getFieldAlias("contragent_inn")).toString());
  role->setContragentAdres(record.value(getFieldAlias("contragent_adres")).toString());
  role->setName(record.value(getFieldAlias("name")).toString());
  role->setComments(record.value(getFieldAlias("comments")).toString());
  return role;
}

BindParamsType PostgresCrud<Role>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{
      {":id_user", filters.value("userId")},
      {":not_id_user", filters.value("notUserId")},
  };
}

BindParamsType PostgresCrud<Role>::getInsertParams(const Editor::Shared &role) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_role", QVariant()},
      {":id_contragent",role->getContragentId()},
      {":name", role->getName()},
      {":comments", role->getComments()},
      };
}

BindParamsType PostgresCrud<Role>::getUpdateParams(const Editor::Shared &role) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_role", role->getId()},
      {":id_contragent",role->getContragentId()},
      {":name", role->getName()},
      {":comments", role->getComments()},
      };
}

void PostgresCrud<Role>::ins(const Editor::Shared& role) const {
  Editor<Role>::ins(role);

  QSet<ID> idsToInsert;
  for (auto user : role->getUsers()) {
    idsToInsert << user->getId();
  }

  insertNewUserToRole(idsToInsert, role);
}

void PostgresCrud<Role>::upd(const Editor::Shared& role) const {
  Editor<Role>::upd(role);

  auto users = role->getUsers();
  QSet<ID> currentIds;
  for (auto user : users) {
    currentIds << user->getId();
  }

  QSet<ID> dbIds = selectCurrentUserIds(role);
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteUserFromRole(idsToDelete, role);
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertNewUserToRole(idsToInsert, role);
  }
}

Editor<Role>::SharedList PostgresCrud<Role>::sel(const IDList& ids) const {
  auto result = Editor<Role>::sel(ids);
  if (getLoadChildren()) {
    for (auto role : result) {
      role->setUsers(selectUsers(role));
    }
  }
  return result;
}

Editor<Role>::SharedList PostgresCrud<Role>::sel(const QVariantHash& filters) const {
  auto result = Editor<Role>::sel(filters);
  if (getLoadChildren()) {
    for (auto role : result) {
      role->setUsers(selectUsers(role));
    }
  }
  return result;
}

UserSharedList PostgresCrud<Role>::selectUsers(const RoleShared& role) const {
  const QString selectAllUserIdSql = "select id_user from user_pkg_i.user_vwf(:id_role, null, null)";
  const BindParamsType bindParamsSelectAllId{
      {":id_role", role->getId()},
      };
  SelectQuery selectUserIds(getSession()->getDb());
  selectUserIds.prepare(selectAllUserIdSql);
  selectUserIds.bind(bindParamsSelectAllId);
  selectUserIds.exec();
  PostgresCrud<User> userCrud;
  userCrud.setSession(getSession());
  UserSharedList users;
  for (auto record : selectUserIds) {
    auto userId = record.value(0).value<ID>();
    users << userCrud.selById(userId);
  }
  return users;
}

QSet<ID> PostgresCrud<Role>::selectCurrentUserIds(const RoleShared& role) const {
  const QString selectAllUserIdSql = "select id_user from user_pkg_i.user_vwf(:id_role, null, null)";
  const BindParamsType bindParamsSelectAllId{
      {":id_role", role->getId()},
      };
  SelectQuery selectUserIds(getSession()->getDb());
  selectUserIds.prepare(selectAllUserIdSql);
  selectUserIds.bind(bindParamsSelectAllId);
  selectUserIds.exec();
  QSet<ID> dbIds;
  for (auto record : selectUserIds) {
    auto id = record.value(0).value<ID>();
    dbIds << id;
  }
  return dbIds;
}

void PostgresCrud<Role>::insertNewUserToRole(const QSet<ID> idsToInsert,
					     const RoleShared& role) const {
  const QString saveItemSql = "select user_pkg_i.ins_user_in_role(:id_role, :id_user)";
  InsertQuery insertItemQuery(getSession()->getDb());
  insertItemQuery.prepare(saveItemSql);
  for (auto id : idsToInsert) {
    const BindParamsType bindParamsInsertGroupItem{
	{":id_role", role->getId()},
	{":id_user", id},
	};
    insertItemQuery.bind(bindParamsInsertGroupItem);
    insertItemQuery.exec();
    insertItemQuery.finish();
  }
}

void PostgresCrud<Role>::deleteUserFromRole(const QSet<ID> idsToDelete,
							    const RoleShared& role) const {
  const QString deleteGroupItemsSql = "select user_pkg_i.del_user_from_role(:id_role, :id_user)";
  DeleteQuery deleteGroupItemQuery(getSession()->getDb());
  deleteGroupItemQuery.prepare(deleteGroupItemsSql);
  for (auto id : idsToDelete) {
    const BindParamsType bindParamsDeleteGroupItem{
	{":id_user", id},
	{":id_role", role->getId()},
	};
    deleteGroupItemQuery.bind(bindParamsDeleteGroupItem);
    deleteGroupItemQuery.exec();
    deleteGroupItemQuery.finish();
  }
}

} // namespace PostgresqlGateway
} // namespace light


