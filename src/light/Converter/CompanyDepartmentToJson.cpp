#include "CompanyDepartmentToJson.h"

#include "CompanyDepartment.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<CompanyDepartment>::toJson(const CompanyDepartmentShared& companyDepartment) const {
  QJsonObject companyDepartmentJson;
  companyDepartmentJson["id"] = QJsonValue::fromVariant(companyDepartment->getId());
  companyDepartmentJson["geographId"] = QJsonValue::fromVariant(companyDepartment->getGeographId());
  companyDepartmentJson["geographCode"] = companyDepartment->getGeographCode();
  companyDepartmentJson["code"] = companyDepartment->getCode();
  companyDepartmentJson["name"] = companyDepartment->getName();
  companyDepartmentJson["inn"] = companyDepartment->getInn();
  companyDepartmentJson["comments"] = companyDepartment->getComments();
  companyDepartmentJson["orgFormId"] = QJsonValue::fromVariant(companyDepartment->getOrgFormId());
  companyDepartmentJson["orgFormCode"] = QJsonValue::fromVariant(companyDepartment->getOrgFormCode());
  return companyDepartmentJson;
}

} // namespace light
