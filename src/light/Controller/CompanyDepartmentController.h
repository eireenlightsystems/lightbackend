#ifndef COMPANYDEPARTMENTCONTROLLER_H
#define COMPANYDEPARTMENTCONTROLLER_H

#include "Controller.h"
#include "CompanyDepartment.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<CompanyDepartment, Crud> : public EditableController<CompanyDepartment, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<CompanyDepartment, Crud>::ins(const QList<QVariantHash>& params) {
  CompanyDepartmentSharedList newCompanyDepartments;
  Crud<Geograph> geographCrud;
  geographCrud.setSession(this->getSession());

  for (const auto& param : params){
    auto newCompanyDepartment = CompanyDepartmentShared::create();

    Crud<Geograph> geographCrud;
    geographCrud.setSession(this->getSession());

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      auto geograph = geographCrud.selById(geographId);
      newCompanyDepartment->setGeograph(geograph);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newCompanyDepartment->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newCompanyDepartment->setName(name);
    }

    if (param.contains("inn")) {
      QString inn = param.value("inn").toString();
      newCompanyDepartment->setInn(inn);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newCompanyDepartment->setComments(comments);
    }

    if (param.contains("orgFormId")) {
      ID orgFormId = param.value("orgFormId").value<ID>();
      newCompanyDepartment->setOrgFormId(orgFormId);
    }

    newCompanyDepartments << newCompanyDepartment;
  }

  Crud<CompanyDepartment> companyDepartmentCrud;
  companyDepartmentCrud.setSession(this->getSession());
  companyDepartmentCrud.save(newCompanyDepartments);
  IDList result;
  std::transform(newCompanyDepartments.begin(), newCompanyDepartments.end(), std::back_inserter(result), [](const CompanyDepartmentShared& companyDepartment) {
    return companyDepartment->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<CompanyDepartment, Crud>::upd(const QList<QVariantHash>& params) {
  CompanyDepartmentSharedList companyDepartments;
  Crud<CompanyDepartment> companyDepartmentCrud;
  companyDepartmentCrud.setSession(this->getSession());
  Crud<Geograph> geographCrud;
  geographCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID companyDepartmentId = param.value("id").value<ID>();
    auto companyDepartment = companyDepartmentCrud.selById(companyDepartmentId);

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      auto geograph = geographCrud.selById(geographId);
      companyDepartment->setGeograph(geograph);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      companyDepartment->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      companyDepartment->setName(name);
    }

    if (param.contains("inn")) {
      QString inn = param.value("inn").toString();
      companyDepartment->setInn(inn);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      companyDepartment->setComments(comments);
    }

    if (param.contains("orgFormId")) {
      ID orgFormId = param.value("orgFormId").value<ID>();
      companyDepartment->setOrgFormId(orgFormId);
    }

    companyDepartments << companyDepartment;
  }

  companyDepartmentCrud.save(companyDepartments);
}

template <template <typename> class Crud>
void Controller<CompanyDepartment, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light


#endif // COMPANYDEPARTMENTCONTROLLER_H
