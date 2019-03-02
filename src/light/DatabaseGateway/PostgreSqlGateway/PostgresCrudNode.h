#ifndef POSTGRESCRUDNODE_H
#define POSTGRESCRUDNODE_H

#include "Node.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template<>
template <>
NodeSharedList PostgresCrud<Node>::sel<ID, ID, ID, ID, ID>(ID geopraphId,
							   ID ownerId,
							   ID nodeTypeId,
							   ID contractId,
							   ID gatewayId) const;

template <>
void PostgresCrud<Node>::ins(const NodeShared& node) const;

template <>
void PostgresCrud<Node>::upd(const NodeShared& node) const;

template <>
void PostgresCrud<Node>::del(const NodeSharedList& nodes) const;

template <>
NodeShared PostgresCrud<Node>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDNODE_H
