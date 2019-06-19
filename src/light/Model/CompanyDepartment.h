#ifndef COMPANYDEPARTMENT_H
#define COMPANYDEPARTMENT_H

#include "Contragent.h"

namespace light {
class CompanyDepartment : public Contragent
{
public:
  CompanyDepartment() = default;

  ID getOrgFormId() const;
  void setOrgFormId(const ID& value);

private:
  ID orgFormId{0};
};
} // namespace light

#endif // COMPANYDEPARTMENT_H
