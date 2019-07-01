#ifndef CONTRACTCONTROLLER_H
#define CONTRACTCONTROLLER_H

#include "Controller.h"
#include "Contract.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Contract, Crud> : public EditableController<Contract, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Contract, Crud>::ins(const QList<QVariantHash>& params) {
  ContractSharedList newContracts;
  for (const auto& param : params){
    auto newContract = ContractShared::create();

    if (param.contains("contractTypeId")) {
      ID contractTypeId = param.value("contractTypeId").value<ID>();
      newContract->setContractTypeId(contractTypeId);
    }

    if (param.contains("senderId")) {
      ID senderId = param.value("senderId").value<ID>();
      newContract->setSenderId(senderId);
    }

    if (param.contains("recipientId")) {
      ID recipientId = param.value("recipientId").value<ID>();
      newContract->setRecipientId(recipientId);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newContract->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newContract->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newContract->setComments(comments);
    }

    newContracts << newContract;
  }

  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  contractCrud.save(newContracts);
  IDList result;
  std::transform(newContracts.begin(), newContracts.end(), std::back_inserter(result), [](const ContractShared& contract) {
    return contract->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Contract, Crud>::upd(const QList<QVariantHash>& params) {
  ContractSharedList contracts;
  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID contractId = param.value("id").value<ID>();
    auto contract = contractCrud.selById(contractId);

    if (param.contains("contractTypeId")) {
      ID contractTypeId = param.value("contractTypeId").value<ID>();
      contract->setContractTypeId(contractTypeId);
    }

    if (param.contains("senderId")) {
      ID senderId = param.value("senderId").value<ID>();
      contract->setSenderId(senderId);
    }

    if (param.contains("recipientId")) {
      ID recipientId = param.value("recipientId").value<ID>();
      contract->setRecipientId(recipientId);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      contract->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      contract->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      contract->setComments(comments);
    }

    contracts << contract;
  }

  contractCrud.save(contracts);
}

template <template <typename> class Crud>
void Controller<Contract, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // CONTRACTCONTROLLER_H
