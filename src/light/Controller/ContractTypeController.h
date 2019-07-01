#ifndef CONTRACTTYPECONTROLLER_H
#define CONTRACTTYPECONTROLLER_H

#include "Controller.h"
#include "ContractType.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<ContractType, Crud> : public EditableController<ContractType, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<ContractType, Crud>::ins(const QList<QVariantHash>& params) {
  ContractTypeSharedList newContractTypes;
  for (const auto& param : params){
    auto newContractType = ContractTypeShared::create();

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newContractType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newContractType->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newContractType->setComments(comments);
    }

    newContractTypes << newContractType;
  }

  Crud<ContractType> contractTypeCrud;
  contractTypeCrud.setSession(this->getSession());
  contractTypeCrud.save(newContractTypes);
  IDList result;
  std::transform(newContractTypes.begin(), newContractTypes.end(), std::back_inserter(result), [](const ContractTypeShared& contractType) {
    return contractType->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<ContractType, Crud>::upd(const QList<QVariantHash>& params) {
  ContractTypeSharedList contractTypes;
  Crud<ContractType> contractTypeCrud;
  contractTypeCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID contractTypeId = param.value("id").value<ID>();
    auto contractType = contractTypeCrud.selById(contractTypeId);

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      contractType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      contractType->setName(name);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      contractType->setComments(comments);
    }

    contractTypes << contractType;
  }

  contractTypeCrud.save(contractTypes);
}

template <template <typename> class Crud>
void Controller<ContractType, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light


#endif // CONTRACTTYPECONTROLLER_H
