#ifndef POSTGRESCRUDFIXTUREGROUPOWNER_H
#define POSTGRESCRUDFIXTUREGROUPOWNER_H

#include "FixtureGroup.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureGroupOwner> : public Reader<FixtureGroupOwner>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREGROUPOWNER_H
