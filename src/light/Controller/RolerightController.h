#ifndef ROLERIGHTCONTROLLER_H
#define ROLERIGHTCONTROLLER_H

#include "Controller.h"
#include "Roleright.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Roleright, Crud> : public EditableController<Roleright, Crud>
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
IDList Controller<Roleright, Crud>::ins(const QList<QVariantHash>& params) {
  RolerightSharedList newRolerights;
  for (const auto& param : params){
    auto newRoleright = RolerightShared::create();

    if (param.contains("roleId")) {
      ID roleId = param.value("roleId").value<ID>();
      newRoleright->setRoleId(roleId);
    }

    if (param.contains("componentCode")) {
      QString componentCode = param.value("componentCode").toString();
      newRoleright->setComponentCode(componentCode);
    }

    newRolerights << newRoleright;
  }

  Crud<Roleright> rolerightCrud;
  rolerightCrud.setSession(this->getSession());
  rolerightCrud.save(newRolerights);
  IDList result;
  std::transform(newRolerights.begin(), newRolerights.end(), std::back_inserter(result), [](const RolerightShared& roleright) {
    return roleright->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Roleright, Crud>::upd(const QList<QVariantHash>& params) {
  Q_UNUSED(params)
}

template <template <typename> class Crud>
void Controller<Roleright, Crud>::upd(ID id, const QVariantHash& param) {
  Q_UNUSED(id)
  Q_UNUSED(param)
}

template <template <typename> class Crud>
void Controller<Roleright, Crud>::del(const IDList& ids) const {
  RolerightSharedList rolerightList;
  for(auto id : ids) {
    RolerightShared roleright = RolerightShared::create();
    roleright->setId(id);
    rolerightList << roleright;
  }
  auto crud = this->createCrud();
  crud.del(rolerightList);
}

} // namespace light

#endif // ROLERIGHTCONTROLLER_H
