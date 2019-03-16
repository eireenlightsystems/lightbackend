#include "PostgresCrudGatewayType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> gatewayTypeFields{
    {"id_gateway_type", "id_gateway_type", true},
    {"code_gateway_type", "code_gateway_type", false},
};

PostgresCrud<GatewayType>::PostgresCrud() {
  setFields(gatewayTypeFields);
  setView("gateway_pkg_i.gateway_type_vw");
}

Reader<GatewayType>::Shared PostgresCrud<GatewayType>::parse(const QSqlRecord& record) const {
  auto gatewayType = GatewayTypeShared::create();
  gatewayType->setId(record.value(getIdAlias()).value<ID>());
  gatewayType->setCode(record.value(getFiledAlias("code_gateway_type")).toString());
  return gatewayType;
}

} // namespace PostgresqlGateway
} // namespace light
