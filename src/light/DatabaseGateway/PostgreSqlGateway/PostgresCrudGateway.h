#ifndef POSTGRESCRUDGATEWAY_H
#define POSTGRESCRUDGATEWAY_H

#include "Gateway.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
GatewaySharedList PostgresCrud<Gateway>::sel(const IDList& ids) const;

template <>
template <>
GatewaySharedList PostgresCrud<Gateway>::sel<ID, ID, ID, ID, ID>(ID geopraphId,
								 ID ownerId,
								 ID gatewayTypeId,
								 ID contractId,
								 ID nodeId) const;

template <>
template <>
GatewaySharedList PostgresCrud<Gateway>::sel<QVariantHash>(const QVariantHash filters) const;

template <>
void PostgresCrud<Gateway>::ins(const GatewayShared& gateway) const;

template <>
void PostgresCrud<Gateway>::upd(const GatewayShared& gateway) const;

template <>
void PostgresCrud<Gateway>::del(const GatewaySharedList& gateways) const;

template <>
GatewayShared PostgresCrud<Gateway>::parse(const QSqlRecord& record) const;

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGATEWAY_H
