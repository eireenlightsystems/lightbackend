#include "PostgresCrudGatewayType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
GatewayTypeSharedList PostgresCrud<GatewayType>::sel<>() const {
  GatewayTypeSharedList result;
  const QString sql = "select id_gateway_type, code_gateway_type "
		      "from gateway_pkg_i.gateway_type_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
GatewayTypeSharedList PostgresCrud<GatewayType>::sel(const IDList& ids) const {
  GatewayTypeSharedList result;
  const QString sql = "select id_gateway_type, code_gateway_type "
		      "from gateway_pkg_i.gateway_type_vw "
		      "where id_gateway_type = :id_gateway_type";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_gateway_type", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
GatewayTypeShared PostgresCrud<GatewayType>::parse(const QSqlRecord& record) const {
  auto gatewayType = GatewayTypeShared::create();
  gatewayType->setId(record.value(0).value<ID>());
  gatewayType->setCode(record.value(1).toString());
  return gatewayType;
}

} // namespace PostgresqlGateway
} // namespace light
