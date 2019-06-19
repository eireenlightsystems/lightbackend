#ifndef COMPANYDEPARTMENTTOJSON_H
#define COMPANYDEPARTMENTTOJSON_H

#include "ToJsonConverter.h"
#include "CompanyDepartment.h"

namespace light {

template <>
class ToJsonConverter<CompanyDepartment> : public ToJsonConverterTemplate<CompanyDepartment>
{
public:
  QJsonObject toJson(const CompanyDepartmentShared& companyDepartment) const override;
};

} // namespace light

#endif // COMPANYDEPARTMENTTOJSON_H
