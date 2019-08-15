#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include "Controller.h"
#include "Role.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Role, Crud> : public EditableController<Role, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Role, Crud>::ins(const QList<QVariantHash>& params) {
  RoleSharedList newRoles;
  for (const auto& param : params){
    auto newRole = RoleShared::create();

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
    ID roleId = param.value("id").value<ID>();
    auto role = roleCrud.selById(roleId);

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
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // ROLECONTROLLER_H
