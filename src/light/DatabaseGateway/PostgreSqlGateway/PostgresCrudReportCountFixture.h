#ifndef POSTGRESCRUDREPORTCOUNTFIXTURE_H
#define POSTGRESCRUDREPORTCOUNTFIXTURE_H


#include "ReportCountFixture.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<ReportCountFixture> : public Editor<ReportCountFixture>
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

#endif // POSTGRESCRUDREPORTCOUNTFIXTURE_H
