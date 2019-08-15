#ifndef SUBSTATIONCONTROLLER_H
#define SUBSTATIONCONTROLLER_H

#include "Controller.h"
#include "Substation.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Substation, Crud> : public EditableController<Substation, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Substation, Crud>::ins(const QList<QVariantHash>& params) {
  SubstationSharedList newSubstations;
  Crud<Geograph> geographCrud;
  geographCrud.setSession(this->getSession());

  for (const auto& param : params){
    auto newSubstation = SubstationShared::create();

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      auto geograph = geographCrud.selById(geographId);
      newSubstation->setGeograph(geograph);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newSubstation->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newSubstation->setName(name);
    }

    if (param.contains("inn")) {
      QString inn = param.value("inn").toString();
      newSubstation->setInn(inn);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newSubstation->setComments(comments);
    }

    if (param.contains("orgFormId")) {
      ID orgFormId = param.value("orgFormId").value<ID>();
      newSubstation->setOrgFormId(orgFormId);
    }

    newSubstations << newSubstation;
  }

  Crud<Substation> substationCrud;
  substationCrud.setSession(this->getSession());
  substationCrud.save(newSubstations);
  IDList result;
  std::transform(newSubstations.begin(), newSubstations.end(), std::back_inserter(result), [](const SubstationShared& substation) {
    return substation->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Substation, Crud>::upd(const QList<QVariantHash>& params) {
  SubstationSharedList substations;
  Crud<Substation> substationCrud;
  substationCrud.setSession(this->getSession());
  Crud<Geograph> geographCrud;
  geographCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID substationId = param.value("id").value<ID>();
    auto substation = substationCrud.selById(substationId);

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      auto geograph = geographCrud.selById(geographId);
      substation->setGeograph(geograph);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      substation->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      substation->setName(name);
    }

    if (param.contains("inn")) {
      QString inn = param.value("inn").toString();
      substation->setInn(inn);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      substation->setComments(comments);
    }

    if (param.contains("orgFormId")) {
      ID orgFormId = param.value("orgFormId").value<ID>();
      substation->setOrgFormId(orgFormId);
    }

    substations << substation;
  }

  substationCrud.save(substations);
}

template <template <typename> class Crud>
void Controller<Substation, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // SUBSTATIONCONTROLLER_H
