#include "PostgresCrudGatewayType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<GatewayType>::PostgresCrud() {
  setIdField("id_gateway_type");
  setFields(QStringList() << getIdField() << "code_gateway_type");
  setView("gateway_pkg_i.gateway_type_vw");
}

Reader<GatewayType>::Shared PostgresCrud<GatewayType>::parse(const QSqlRecord& record) const {
  auto gatewayType = GatewayTypeShared::create();
  gatewayType->setId(record.value(0).value<ID>());
  gatewayType->setCode(record.value(1).toString());
  return gatewayType;
}

} // namespace PostgresqlGateway
} // namespace light
