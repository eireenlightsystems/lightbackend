#ifndef POSTGRESCRUDNODETYPE_H
#define POSTGRESCRUDNODETYPE_H

#include "NodeType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
NodeTypeSharedList PostgresCrud<NodeType>::sel<>() const;

template <>
NodeTypeSharedList PostgresCrud<NodeType>::sel(const IDList& ids) const;

template <>
NodeTypeShared PostgresCrud<NodeType>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDNODETYPE_H
