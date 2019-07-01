#include "PostgresCrudContractType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> contractFields {
    {"id_contract_type", "id_contract_type", true},
    {"code", "code_contract_type", false},
    {"name", "name_contract_type", false},
    {"comments", "comments_contract_type", false},
};

PostgresCrud<ContractType>::PostgresCrud() {
  setFields(contractFields);
  setView("contract_type_pkg_i.contract_type_vwf()");
  setInsertSql("select contract_type_pkg_i.save(:action, :id_contract_type, :code, :name, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select contract_type_pkg_i.del(:id)");
}

Reader<ContractType>::Shared PostgresCrud<ContractType>::parse(const QSqlRecord& record) const {
  auto contractType = ContractTypeShared::create();
  contractType->setId(record.value(getFieldAlias("id_contract_type")).value<ID>());
  contractType->setCode(record.value(getFieldAlias("code")).toString());
  contractType->setName(record.value(getFieldAlias("name")).toString());
  contractType->setComments(record.value(getFieldAlias("comments")).toString());
  return contractType;
}

BindParamsType PostgresCrud<ContractType>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<ContractType>::getInsertParams(const Editor::Shared &contractType) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_contract_type", QVariant()},
      {":code", contractType->getCode()},
      {":name", contractType->getName()},
      {":comments", contractType->getComments()},
  };
}

BindParamsType PostgresCrud<ContractType>::getUpdateParams(const Editor::Shared &contractType) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_contract_type", QVariant()},
      {":code", contractType->getCode()},
      {":name", contractType->getName()},
      {":comments", contractType->getComments()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
