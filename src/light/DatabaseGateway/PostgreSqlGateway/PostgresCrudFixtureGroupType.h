#ifndef POSTGRESCRUDFIXTUREGROUPTYPE_H
#define POSTGRESCRUDFIXTUREGROUPTYPE_H

#include "FixtureGroupType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureGroupType> : public Reader<FixtureGroupType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREGROUPTYPE_H
