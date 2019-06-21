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

  QString getOrgFormCode() const;
  void setOrgFormCode(const QString& value);

private:
  ID orgFormId{0};
  QString orgFormCode;
};
} // namespace light

#endif // COMPANYDEPARTMENT_H
