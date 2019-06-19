#ifndef FIXTURECONTROLLER_H
#define FIXTURECONTROLLER_H

#include "Controller.h"
#include "Fixture.h"
#include "FixtureHeightType.h"
#include "Substation.h"
#include "FixtureType.h"
#include "Contract.h"
#include "Node.h"

#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Controller<Fixture, Crud> : public EditableController<Fixture, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Fixture, Crud>::ins(const QList<QVariantHash>& params) {
  FixtureSharedList newFixtures;

  Crud<Contragent> contragentCrud;
  contragentCrud.setSession(this->getSession());
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  Crud<FixtureType> fixtureTypeCrud;
  fixtureTypeCrud.setSession(this->getSession());
  Crud<FixtureHeightType> fixtureHeightTypeCrud;
  fixtureHeightTypeCrud.setSession(this->getSession());
  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<Substation> substationCrud;
  substationCrud.setSession(this->getSession());

  for (const auto& param : params) {
    auto newFixture = FixtureShared::create();

    if (param.contains("nodeId")) {
      ID nodeId = param.value("nodeId").value<ID>();
      auto node = nodeCrud.selById(nodeId);
      newFixture->setNode(node);
    }

    if (param.contains("fixtureTypeId")) {
      ID fixtureTypeId = param.value("fixtureTypeId").value<ID>();
      auto fixtureType = fixtureTypeCrud.selById(fixtureTypeId);
      newFixture->setType(fixtureType);
    }

    if (param.contains("heightTypeId")) {
      ID heightTypeId = param.value("heightTypeId").value<ID>();
      auto heightType = fixtureHeightTypeCrud.selById(heightTypeId);
      newFixture->setHeightType(heightType);
    }

    /// TODO Add owner
    //      newFixture->setOwner(contragentCrud.selById(param.));

    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      auto contract = contractCrud.selById(contractId);
      newFixture->setContract(contractCrud.selById(contractId));
    }

    if (param.contains("installerId")) {
      ID installerId = param.value("installerId").value<ID>();
      auto installer = contragentCrud.selById(installerId);
      newFixture->setInstaller(installer);
    }

    if (param.contains("substationId")) {
      ID substationId = param.value("substationId").value<ID>();
      auto substation = substationCrud.selById(substationId);
      newFixture->setSubstation(substation);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      newFixture->setComment(comment);
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      newFixture->setSerialNumber(serialNumber);
    }

    newFixtures << newFixture;
  }

  Crud<Fixture> fixtureCrud;
  fixtureCrud.setSession(this->getSession());
  fixtureCrud.save(newFixtures);
  IDList result;
  std::transform(newFixtures.begin(), newFixtures.end(), std::back_inserter(result), [](const FixtureShared& fixture) {
    return fixture->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Fixture, Crud>::upd(const QList<QVariantHash>& params) {
  FixtureSharedList fixtures;

  Crud<Fixture> fixtureCrud;
  fixtureCrud.setSession(this->getSession());
  Crud<Contragent> contragentCrud;
  contragentCrud.setSession(this->getSession());
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  Crud<FixtureType> fixtureTypeCrud;
  fixtureTypeCrud.setSession(this->getSession());
  Crud<FixtureHeightType> fixtureHeightTypeCrud;
  fixtureHeightTypeCrud.setSession(this->getSession());
  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<Substation> substationCrud;
  substationCrud.setSession(this->getSession());

  for (const auto& param : params) {
    ID fixtureId = param.value("fixtureId").value<ID>();
    auto fixture = fixtureCrud.selById(fixtureId);

    if (param.contains("nodeId")) {
      ID nodeId = param.value("nodeId").value<ID>();
      auto node = nodeCrud.selById(nodeId);
      fixture->setNode(node);
    }

    if (param.contains("fixtureTypeId")) {
      ID fixtureTypeId = param.value("fixtureTypeId").value<ID>();
      auto fixtureType = fixtureTypeCrud.selById(fixtureTypeId);
      fixture->setType(fixtureType);
    }

    if (param.contains("heightTypeId")) {
      ID heightTypeId = param.value("heightTypeId").value<ID>();
      auto heightType = fixtureHeightTypeCrud.selById(heightTypeId);
      fixture->setHeightType(heightType);
    }

    /// TODO Add owner
    //      newFixture->setOwner(contragentCrud.selById(param.));

    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      auto contract = contractCrud.selById(contractId);
      fixture->setContract(contractCrud.selById(contractId));
    }

    if (param.contains("installerId")) {
      ID installerId = param.value("installerId").value<ID>();
      auto installer = contragentCrud.selById(installerId);
      fixture->setInstaller(installer);
    }

    if (param.contains("substationId")) {
      ID substationId = param.value("substationId").value<ID>();
      auto substation = substationCrud.selById(substationId);
      fixture->setSubstation(substation);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      fixture->setComment(comment);
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      fixture->setSerialNumber(serialNumber);
    }

    fixtures << fixture;
  }

  fixtureCrud.save(fixtures);
}

template <template <typename> class Crud>
void Controller<Fixture, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["fixtureId"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // FIXTURECONTROLLER_H
