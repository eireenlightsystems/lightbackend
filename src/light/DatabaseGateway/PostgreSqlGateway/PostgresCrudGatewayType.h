#ifndef POSTGRESCRUDGATEWAYTYPE_H
#define POSTGRESCRUDGATEWAYTYPE_H

#include "GatewayType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
template <>
GatewayTypeSharedList PostgresCrud<GatewayType>::sel<>() const;

template <>
GatewayTypeSharedList PostgresCrud<GatewayType>::sel(const IDList& ids) const;

template <>
GatewayTypeShared PostgresCrud<GatewayType>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGATEWAYTYPE_H
