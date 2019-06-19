#ifndef POSTGRESCRUDCOMPANYDEPARTMENT_H
#define POSTGRESCRUDCOMPANYDEPARTMENT_H

#include "CompanyDepartment.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<CompanyDepartment> : public Editor<CompanyDepartment>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDCOMPANYDEPARTMENT_H
