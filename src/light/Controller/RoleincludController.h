#ifndef ROLEINCLUDCONTROLLER_H
#define ROLEINCLUDCONTROLLER_H

#include "Controller.h"
#include "Roleinclud.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Roleinclud, Crud> : public EditableController<Roleinclud, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
  void del(const IDList& ids) const override;
};

template <template <typename> class Crud>
IDList Controller<Roleinclud, Crud>::ins(const QList<QVariantHash>& params) {
  RoleincludSharedList newRoleincluds;
  for (const auto& param : params){
    auto newRoleinclud = RoleincludShared::create();

    if (param.contains("roleId")) {
      ID roleId = param.value("roleId").value<ID>();
      newRoleinclud->setRoleId(roleId);
    }

    if (param.contains("userId")) {
      ID userId = param.value("userId").value<ID>();
      newRoleinclud->setUserId(userId);
    }

    newRoleincluds << newRoleinclud;
  }

  Crud<Roleinclud> roleincludCrud;
  roleincludCrud.setSession(this->getSession());
  roleincludCrud.save(newRoleincluds);
  IDList result;
  std::transform(newRoleincluds.begin(), newRoleincluds.end(), std::back_inserter(result), [](const RoleincludShared& roleinclud) {
    return roleinclud->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Roleinclud, Crud>::upd(const QList<QVariantHash>& params) {
  Q_UNUSED(params)
}

template <template <typename> class Crud>
void Controller<Roleinclud, Crud>::upd(ID id, const QVariantHash& param) {
  Q_UNUSED(id)
  Q_UNUSED(param)
}

template <template <typename> class Crud>
void Controller<Roleinclud, Crud>::del(const IDList& ids) const {
  RoleincludSharedList roleincludList;
  for(auto id : ids) {
    RoleincludShared roleinclud = RoleincludShared::create();
    roleinclud->setId(id);
    roleincludList << roleinclud;
  }
  auto crud = this->createCrud();
  crud.del(roleincludList);
}

} // namespace light

#endif // ROLEINCLUDCONTROLLER_H
