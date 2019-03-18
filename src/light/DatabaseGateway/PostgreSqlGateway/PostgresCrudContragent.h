#ifndef POSTGRESCRUDCONTRAGENT_H
#define POSTGRESCRUDCONTRAGENT_H

#include "Contragent.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Contragent> : public Reader<Contragent>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDCONTRAGENT_H
