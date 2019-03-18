#ifndef POSTGRESCRUDGEOGRAPH_H
#define POSTGRESCRUDGEOGRAPH_H

#include "Geograph.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Geograph> : public Reader<Geograph>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGEOGRAPH_H
