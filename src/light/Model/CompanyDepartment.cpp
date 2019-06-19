#include "CompanyDepartment.h"

namespace light {


ID CompanyDepartment::getOrgFormId() const {
  return orgFormId;
}

void CompanyDepartment::setOrgFormId(const ID& value) {
  orgFormId = value;
}

} // namespace light
