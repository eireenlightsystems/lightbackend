#ifndef POSTGRESCRUDNODE_H
#define POSTGRESCRUDNODE_H

#include "Node.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Node> : public Editor<Node>
{
public:
  PostgresCrud();

protected:
  Shared parse(const QSqlRecord& record) const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDNODE_H
