#include "PostgresCrudCompanyDepartment.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> companyDepartmentFields{
    {"id_contragent", "id_contragent_company_department", true},
    {"id_geograph_addr", "id_geograph_addr_company_department", true},
    {"code_geograph", "code_geograph_company_department", true},
    {"code", "code_company_department", false},
    {"name", "name_company_department", false},
    {"inn", "inn_company_department", false},
    {"comments", "comments_company_department", false},
    {"id_org_forms_type", "id_org_forms_type_company_department", true},
    {"code_org_forms_type", "code_org_forms_type_company_department", true},
};

PostgresCrud<CompanyDepartment>::PostgresCrud() {
  setFields(companyDepartmentFields);
  setView("company_department_pkg_i.company_department_vwf()");
  setInsertSql("select company_department_pkg_i.save(:action, :id_contragent, :id_geograph_addr, :code, :name, :inn, :comments, :id_org_forms_type)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select company_department_pkg_i.del(:id)");
}

Reader<CompanyDepartment>::Shared PostgresCrud<CompanyDepartment>::parse(const QSqlRecord& record) const {
  auto companyDepartment = CompanyDepartmentShared::create();
  companyDepartment->setId(record.value(getFieldAlias("id_contragent")).value<ID>());
  companyDepartment->setGeographId(record.value(getFieldAlias("id_geograph_addr")).value<ID>());
  companyDepartment->setGeographCode(record.value(getFieldAlias("code_geograph")).toString());
  companyDepartment->setCode(record.value(getFieldAlias("code")).toString());
  companyDepartment->setName(record.value(getFieldAlias("name")).toString());
  companyDepartment->setInn(record.value(getFieldAlias("inn")).toString());
  companyDepartment->setComments(record.value(getFieldAlias("comments")).toString());
  companyDepartment->setOrgFormId(record.value(getFieldAlias("id_org_forms_type")).value<ID>());
  companyDepartment->setOrgFormCode(record.value(getFieldAlias("code_org_forms_type")).toString());
  return companyDepartment;
}


BindParamsType PostgresCrud<CompanyDepartment>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<CompanyDepartment>::getInsertParams(const Editor::Shared &companyDepartment) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_contragent", QVariant()},
      {":id_geograph_addr", companyDepartment->getGeographId()},
      {":code", companyDepartment->getCode()},
      {":name", companyDepartment->getName()},
      {":inn", companyDepartment->getInn()},
      {":comments", companyDepartment->getComments()},
      {":id_org_forms_type", companyDepartment->getOrgFormId()},
  };
}

BindParamsType PostgresCrud<CompanyDepartment>::getUpdateParams(const Editor::Shared &companyDepartment) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_contragent", QVariant()},
      {":id_geograph_addr", companyDepartment->getGeographId()},
      {":code", companyDepartment->getCode()},
      {":name", companyDepartment->getName()},
      {":inn", companyDepartment->getInn()},
      {":comments", companyDepartment->getComments()},
      {":id_org_forms_type", companyDepartment->getOrgFormId()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
