#ifndef POSTGRESCRUDFIXTUREHEIGHTTYPE_H
#define POSTGRESCRUDFIXTUREHEIGHTTYPE_H

#include "FixtureHeightType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureHeightType> : public Reader<FixtureHeightType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREHEIGHTTYPE_H
