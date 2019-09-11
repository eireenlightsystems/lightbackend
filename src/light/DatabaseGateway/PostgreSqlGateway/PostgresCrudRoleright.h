#ifndef POSTGRESCRUDROLERIGHT_H
#define POSTGRESCRUDROLERIGHT_H


#include "Roleright.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Roleright> : public Editor<Roleright>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDROLERIGHT_H
