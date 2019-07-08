#include "CompanyDepartmentToJson.h"

#include "CompanyDepartment.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "ContragentToJson.h"

namespace light {

QJsonObject ToJsonConverter<CompanyDepartment>::toJson(const CompanyDepartmentShared& companyDepartment) const {
  ToJsonConverter<Contragent> contragentToJsonConverter;
  QJsonObject companyDepartmentJson = contragentToJsonConverter.toJson(companyDepartment);
  companyDepartmentJson["orgFormId"] = QJsonValue::fromVariant(companyDepartment->getOrgFormId());
  companyDepartmentJson["orgFormCode"] = QJsonValue::fromVariant(companyDepartment->getOrgFormCode());
  return companyDepartmentJson;
}

} // namespace light
