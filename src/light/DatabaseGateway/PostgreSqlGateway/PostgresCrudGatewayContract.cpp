#include "PostgresCrudGatewayContract.h"

#include "PostgresCrudContract.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> gatewayContractFields{
    {"id_contract", "id_contract", true},
    {"code_contract", "code_contract", false},
    {"name_contract", "name_contract", false},
};

PostgresCrud<GatewayContract>::PostgresCrud() {
  setFields(gatewayContractFields);
  setView("gateway_pkg_i.contract_vw");
}

Reader<GatewayContract>::Shared PostgresCrud<GatewayContract>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contract> contractCrud;
  auto contract = contractCrud.parse(record);
  auto gatewatContractOwner = GatewayContractShared::create(*contract);
  return gatewatContractOwner;
}

} // namespace PostgresqlGateway
} // namespace light
