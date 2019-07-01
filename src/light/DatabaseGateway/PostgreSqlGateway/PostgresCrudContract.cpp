#include "PostgresCrudContract.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> contractFields {
    {"id_contract", "id_contract", true},
    {"id_contract_type", "id_contract_type_contract", true},
    {"id_sender", "id_sender_contract", true},
    {"id_recipient", "id_recipient_contract", true},
    {"code_contract_type", "code_contract_type_contract", true},
    {"code_sender", "code_sender_contract", true},
    {"code_recipient", "code_recipient_contract", true},
    {"code", "code_contract", false},
    {"name", "name_contract", false},
    {"comments", "comments_contract", false},
};

PostgresCrud<Contract>::PostgresCrud() {
  setFields(contractFields);
  setView("contract_pkg_i.contract_vwf()");
  setInsertSql("select contract_pkg_i.save(:action, :id_contract, :id_contract_type, :id_sender, :id_recipient, :code, :name, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select contract_pkg_i.del(:id)");
}

Reader<Contract>::Shared PostgresCrud<Contract>::parse(const QSqlRecord& record) const {
  auto contract = ContractShared::create();
  contract->setId(record.value(getFieldAlias("id_contract")).value<ID>());
  contract->setContractTypeId(record.value(getFieldAlias("id_contract_type")).value<ID>());
  contract->setSenderId(record.value(getFieldAlias("id_sender")).value<ID>());
  contract->setRecipientId(record.value(getFieldAlias("id_recipient")).value<ID>());
  contract->setContractTypeCode(record.value(getFieldAlias("code_contract_type")).toString());
  contract->setSenderCode(record.value(getFieldAlias("code_sender")).toString());
  contract->setRecipientCode(record.value(getFieldAlias("code_recipient")).toString());
  contract->setCode(record.value(getFieldAlias("code")).toString());
  contract->setName(record.value(getFieldAlias("name")).toString());
  contract->setComments(record.value(getFieldAlias("comments")).toString());
  return contract;
}

BindParamsType PostgresCrud<Contract>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<Contract>::getInsertParams(const Editor::Shared &contract) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_contract", QVariant()},
      {":id_contract_type", contract->getContractTypeId()},
      {":id_sender", contract->getSenderId()},
      {":id_recipient", contract->getRecipientId()},
      {":code_contract_type", contract->getContractTypeCode()},
      {":code_sender", contract->getSenderCode()},
      {":code_recipient", contract->getRecipientCode()},
      {":code", contract->getCode()},
      {":name", contract->getName()},
      {":comments", contract->getComments()},
  };
}

BindParamsType PostgresCrud<Contract>::getUpdateParams(const Editor::Shared &contract) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_contract", QVariant()},
      {":id_contract_type", contract->getContractTypeId()},
      {":id_sender", contract->getSenderId()},
      {":id_recipient", contract->getRecipientId()},
      {":code_contract_type", contract->getContractTypeCode()},
      {":code_sender", contract->getSenderCode()},
      {":code_recipient", contract->getRecipientCode()},
      {":code", contract->getCode()},
      {":name", contract->getName()},
      {":comments", contract->getComments()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
