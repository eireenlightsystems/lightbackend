#include "CompanyDepartment.h"

namespace light {


ID CompanyDepartment::getOrgFormId() const {
  return orgFormId;
}

void CompanyDepartment::setOrgFormId(const ID& value) {
  orgFormId = value;
}


void CompanyDepartment::setOrgFormCode(const QString& value) {
  orgFormCode = value;
}

QString CompanyDepartment::getOrgFormCode() const {
  return orgFormCode;
}

} // namespace light
