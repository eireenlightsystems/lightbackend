#ifndef FIXTURECONTROLLER_H
#define FIXTURECONTROLLER_H

#include "Controller.h"
#include "Fixture.h"

#include <Node.h>

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
  void ins(const QList<FixtureInsertParameters>& params) {
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
      newFixture->setNode(nodeCrud.selById(param.nodeId));
      newFixture->setType(fixtureTypeCrud.selById(param.fixtureTypeId));
      newFixture->setHeightType(fixtureHeightTypeCrud.selById(param.heightTypeId));
      /// TODO Add owner
      //      newFixture->setOwner(contragentCrud.selById(param.));
      newFixture->setContract(contractCrud.selById(param.contractId));
      newFixture->setInstaller(contragentCrud.selById(param.installerId));
      newFixture->setSubstation(substationCrud.selById(param.substationId));
      newFixture->setPrice(param.price);
      newFixture->setComment(param.comment);

      newFixtures << newFixture;
    }

    Crud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    fixtureCrud.save(newFixtures);
  }
};

template <template <typename> class Crud>
class Updater<Fixture, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<FixtureUpdateParameters>& params) {
    FixtureSharedList fixtures;

    Crud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    Crud<FixtureType> fixtureTypeCrud;
    fixtureTypeCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<Substation> substationCrud;
    substationCrud.setSession(getSession());

    for (const auto& param : params) {
      auto fixture = fixtureCrud.selById(param.fixtureId);
      fixture->setNode(nodeCrud.selById(param.nodeId));
      fixture->setType(fixtureTypeCrud.selById(param.fixtureTypeId));
      /// TODO Add owner
      //      newFixture->setOwner(contragentCrud.selById(param.));
      fixture->setContract(contractCrud.selById(param.contractId));
      fixture->setInstaller(contragentCrud.selById(param.installerId));
      fixture->setSubstation(substationCrud.selById(param.substationId));
      fixture->setPrice(param.price);
      fixture->setComment(param.comment);

      fixtures << fixture;
    }

    fixtureCrud.save(fixtures);
  }
};

} // namespace light

#endif // FIXTURECONTROLLER_H
