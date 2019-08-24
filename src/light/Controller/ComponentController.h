#ifndef COMPONENTCONTROLLER_H
#define COMPONENTCONTROLLER_H

#include "Controller.h"
#include "Component.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Component, Crud> : public EditableController<Component, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Component, Crud>::ins(const QList<QVariantHash>& params) {
  ComponentSharedList newComponents;
  for (const auto& param : params){
    auto newComponent = ComponentShared::create();

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newComponent->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newComponent->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newComponent->setComments(comments);
    }

    newComponents << newComponent;
  }

  Crud<Component> componentCrud;
  componentCrud.setSession(this->getSession());
  componentCrud.save(newComponents);
  IDList result;
  std::transform(newComponents.begin(), newComponents.end(), std::back_inserter(result), [](const ComponentShared& component) {
    return component->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Component, Crud>::upd(const QList<QVariantHash>& params) {
  ComponentSharedList components;
  Crud<Component> componentCrud;
  componentCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID componentId = param.value("componentId").value<ID>();
    auto component = componentCrud.selById(componentId);

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      component->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      component->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      component->setComments(comments);
    }

    components << component;
  }

  componentCrud.save(components);
}

template <template <typename> class Crud>
void Controller<Component, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["componentId"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // COMPONENTCONTROLLER_H
