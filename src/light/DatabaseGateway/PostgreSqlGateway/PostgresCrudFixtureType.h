#ifndef POSTGRESCRUDFIXTURETYPE_H
#define POSTGRESCRUDFIXTURETYPE_H

#include "FixtureType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureType> : public Reader<FixtureType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTURETYPE_H
