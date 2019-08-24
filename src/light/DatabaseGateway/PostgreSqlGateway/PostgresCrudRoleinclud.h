#ifndef POSTGRESCRUDROLEINCLUD_H
#define POSTGRESCRUDROLEINCLUD_H


#include "Roleinclud.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Roleinclud> : public Editor<Roleinclud>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
protected:

  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDROLEINCLUD_H
