#include "PostgresCrudContract.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
ContractSharedList PostgresCrud<Contract>::sel<const IDList&>(const IDList& ids) const {
  ContractSharedList result;
  const QString sql = "select id_contract, code_contract, name_contract "
		      "from contract_pkg_i.contract_show_vw "
		      "where id_contract = :id_contract";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_contract", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
ContractShared PostgresCrud<Contract>::parse(const QSqlRecord& record) const {
  auto contract = ContractShared::create();
  contract->setId(record.value(0).value<ID>());
  contract->setCode(record.value(1).toString());
  contract->setName(record.value(2).toString());
  return contract;
}

} // namespace PostgresqlGateway
} // namespace light
