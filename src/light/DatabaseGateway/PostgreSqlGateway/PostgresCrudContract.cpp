#include "PostgresCrudContract.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> contractFields {
    {"id_contract", "id_contract", true},
    {"code_contract", "code_contract", false},
    {"name_contract", "name_contract", false},
};

PostgresCrud<Contract>::PostgresCrud() {
  setFields(contractFields);
  setView("contract_pkg_i.contract_show_vw");
}

Reader<Contract>::Shared PostgresCrud<Contract>::parse(const QSqlRecord& record) const {
  auto contract = ContractShared::create();
  contract->setId(record.value(getIdAlias()).value<ID>());
  contract->setCode(record.value(getFiledAlias("code_contract")).toString());
  contract->setName(record.value(getFiledAlias("name_contract")).toString());
  return contract;
}

} // namespace PostgresqlGateway
} // namespace light
