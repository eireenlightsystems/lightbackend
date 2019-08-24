#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include "Controller.h"
#include "Role.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Role, Crud> : public EditableListController<Role, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
  void delFromList(ID listId, const IDList& ids) override;
  void addToList(ID listId, const IDList& ids) override;
};

template <template <typename> class Crud>
IDList Controller<Role, Crud>::ins(const QList<QVariantHash>& params) {
  RoleSharedList newRoles;
  for (const auto& param : params){
    auto newRole = RoleShared::create();

    if (param.contains("contragentId")) {
      ID contragentId = param.value("contragentId").value<ID>();
      newRole->setContragentId(contragentId);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newRole->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newRole->setComments(comments);
    }

    newRoles << newRole;
  }

  Crud<Role> roleCrud;
  roleCrud.setSession(this->getSession());
  roleCrud.save(newRoles);
  IDList result;
  std::transform(newRoles.begin(), newRoles.end(), std::back_inserter(result), [](const RoleShared& role) {
    return role->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Role, Crud>::upd(const QList<QVariantHash>& params) {
  RoleSharedList roles;
  Crud<Role> roleCrud;
  roleCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID roleId = param.value("roleId").value<ID>();
    auto role = roleCrud.selById(roleId);

    if (param.contains("contragentId")) {
      ID contragentId = param.value("contragentId").value<ID>();
      role->setContragentId(contragentId);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      role->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      role->setComments(comments);
    }

    roles << role;
  }

  roleCrud.save(roles);
}

template <template <typename> class Crud>
void Controller<Role, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["roleId"] = id;
  return upd({fullParam});
}

template <template <typename> class Crud>
void Controller<Role, Crud>::delFromList(ID listId, const IDList& ids) {
  Crud<Role> roleCrud;
  roleCrud.setSession(this->getSession());
  RoleShared role = roleCrud.selById(listId);
  for (ID id : ids) {
    role->removeUser(id);
  }
  roleCrud.save({role});
}

template <template <typename> class Crud>
void Controller<Role, Crud>::addToList(ID listId, const IDList& ids) {
  Crud<Role> roleCrud;
  roleCrud.setSession(this->getSession());
  RoleShared role = roleCrud.selById(listId);

  Crud<User> userCrud;
  userCrud.setSession(this->getSession());
  for (auto id : ids) {
    auto user = userCrud.selById(id);
    role->addUser(user);
  }
  roleCrud.save({role});
}

} // namespace light

#endif // ROLECONTROLLER_H
