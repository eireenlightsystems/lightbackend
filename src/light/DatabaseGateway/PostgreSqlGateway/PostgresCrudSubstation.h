#ifndef POSTGRESCRUDSUBSTATION_H
#define POSTGRESCRUDSUBSTATION_H

#include "PostgresCrud.h"
#include "Substation.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Substation> : public Reader<Substation>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDSUBSTATION_H
