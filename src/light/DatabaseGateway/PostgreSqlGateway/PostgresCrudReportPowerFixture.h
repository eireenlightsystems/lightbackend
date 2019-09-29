#ifndef POSTGRESCRUDREPORTPOWERFIXTURE_H
#define POSTGRESCRUDREPORTPOWERFIXTURE_H


#include "ReportPowerFixture.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<ReportPowerFixture> : public Editor<ReportPowerFixture>
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

#endif // POSTGRESCRUDREPORTPOWERFIXTURE_H
