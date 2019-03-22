#ifndef SCHEDULERFIXTUREPOSTGRESCRUD_H
#define SCHEDULERFIXTUREPOSTGRESCRUD_H

#include "PostgresCrud.h"
#include "SchedulerFixture.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<CommandsScheduler::SchedulerFixture> : public Editor<CommandsScheduler::SchedulerFixture>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& fixture) const override;
  BindParamsType getUpdateParams(const Shared& fixture) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // SCHEDULERFIXTUREPOSTGRESCRUD_H
