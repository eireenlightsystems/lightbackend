#include "PostgresCrudContract.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<Contract>::PostgresCrud() {
  setIdField("id_contract");
  setFields(QStringList() << getIdField() << "code_contract"
			  << "name_contract");
  setView("contract_pkg_i.contract_show_vw");
}

Reader<Contract>::Shared PostgresCrud<Contract>::parse(const QSqlRecord& record) const {
  auto contract = ContractShared::create();
  contract->setId(record.value(0).value<ID>());
  contract->setCode(record.value(1).toString());
  contract->setName(record.value(2).toString());
  return contract;
}

} // namespace PostgresqlGateway
} // namespace light
