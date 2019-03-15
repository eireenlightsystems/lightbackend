#ifndef FIXTURECONTROLLER_H
#define FIXTURECONTROLLER_H

#include "Contract.h"
#include "Controller.h"
#include "Fixture.h"
#include "FixtureHeightType.h"
#include "FixtureType.h"
#include "Node.h"
#include "Substation.h"

#include <QVariant>

namespace light {

struct FixtureInsertParameters
{
  ID contractId;
  ID fixtureTypeId;
  ID installerId;
  ID substationId;
  ID heightTypeId;
  ID nodeId;
  double price;
  QString comment;
};

struct FixtureUpdateParameters : public FixtureInsertParameters
{
  ID fixtureId;
};

template <template <typename> class Crud>
class Inserter<Fixture, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  IDList ins(const QList<QVariantHash>& params) {
    FixtureSharedList newFixtures;

    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    Crud<FixtureType> fixtureTypeCrud;
    fixtureTypeCrud.setSession(getSession());
    Crud<FixtureHeightType> fixtureHeightTypeCrud;
    fixtureHeightTypeCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<Substation> substationCrud;
    substationCrud.setSession(getSession());

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

      if (param.contains("price")) {
	double price = param.value("price").toDouble();
	newFixture->setPrice(price);
      }

      if (param.contains("comment")) {
	QString comment = param.value("comment").toString();
	newFixture->setComment(comment);
      }

      newFixtures << newFixture;
    }

    Crud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    fixtureCrud.save(newFixtures);
    IDList result;
    std::transform(newFixtures.begin(),
		   newFixtures.end(),
		   std::back_inserter(result),
		   [](const FixtureShared& fixture) { return fixture->getId(); });
    return result;
  }
};

template <template <typename> class Crud>
class Updater<Fixture, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<QVariantHash>& params) {
    FixtureSharedList fixtures;

    Crud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    Crud<FixtureType> fixtureTypeCrud;
    fixtureTypeCrud.setSession(getSession());
    Crud<FixtureHeightType> fixtureHeightTypeCrud;
    fixtureHeightTypeCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<Substation> substationCrud;
    substationCrud.setSession(getSession());

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

      if (param.contains("price")) {
	double price = param.value("price").toDouble();
	fixture->setPrice(price);
      }

      if (param.contains("comment")) {
	QString comment = param.value("comment").toString();
	fixture->setComment(comment);
      }

      fixtures << fixture;
    }

    fixtureCrud.save(fixtures);
  }

  void upd(ID id, const QVariantHash& param) {
    Crud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    Crud<FixtureType> fixtureTypeCrud;
    fixtureTypeCrud.setSession(getSession());
    Crud<FixtureHeightType> fixtureHeightTypeCrud;
    fixtureHeightTypeCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<Substation> substationCrud;
    substationCrud.setSession(getSession());

    auto fixture = fixtureCrud.selById(id);
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

    if (param.contains("price")) {
      double price = param.value("price").toDouble();
      fixture->setPrice(price);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      fixture->setComment(comment);
    }
    fixtureCrud.save({fixture});
  }
};

} // namespace light

#endif // FIXTURECONTROLLER_H
