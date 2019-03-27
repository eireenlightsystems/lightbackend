#ifndef POSTGRESCRUDFIXTURE_H
#define POSTGRESCRUDFIXTURE_H

#include "Fixture.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Fixture> : public Editor<Fixture>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

template <>
class PostgresCrud<FixtureContract> : public Reader<FixtureContract>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

template <>
class PostgresCrud<FixtureOwner> : public Reader<FixtureOwner>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light
#endif // POSTGRESCRUDFIXTURE_H
