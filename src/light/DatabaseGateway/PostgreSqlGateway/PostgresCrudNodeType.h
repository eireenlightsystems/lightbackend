#ifndef POSTGRESCRUDNODETYPE_H
#define POSTGRESCRUDNODETYPE_H

#include "NodeType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<NodeType> : public Reader<NodeType>
{
public:
  PostgresCrud();

protected:
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDNODETYPE_H
