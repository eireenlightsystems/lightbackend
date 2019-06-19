#ifndef COMPANYDEPARTMENTRESTROUTER_H
#define COMPANYDEPARTMENTRESTROUTER_H

#include "CompanyDepartment.h"
#include "CompanyDepartmentController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudCompanyDepartment.h"
#include "CompanyDepartmentToJson.h"

namespace light {

template <>
class RestRouter<CompanyDepartment> : public SimpleEditableRouter<CompanyDepartment>
{
public:
  QString getName() const override {
    return "companies";
  }
};

}

#endif // COMPANYDEPARTMENTRESTROUTER_H
