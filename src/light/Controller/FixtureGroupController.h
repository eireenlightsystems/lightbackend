#ifndef FIXTUREGROUPCONTROLLER_H
#define FIXTUREGROUPCONTROLLER_H

#include "Controller.h"
#include "Fixture.h"
#include "FixtureGroup.h"

namespace light {

struct FixtureGroupInsertParameters
{
  ID groupTypeId;
  ID ownerId;
  QString name;
};

struct FixtureGroupUpdateParameters : public FixtureGroupInsertParameters
{
  ID groupId;
};

template <template <typename> class Crud>
class Inserter<FixtureGroup, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void ins(const QList<FixtureGroupInsertParameters>& params) {
    FixtureGroupSharedList newFixtureGroups;

    Crud<FixtureGroupType> fixtureGroupTypeCrud;
    fixtureGroupTypeCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());

    for (const auto& param : params) {
      auto newFixtureGroup = FixtureGroupShared::create();
      newFixtureGroup->setName(param.name);
      newFixtureGroup->setType(fixtureGroupTypeCrud.selById(param.groupTypeId));
      newFixtureGroup->setOwner(contragentCrud.selById(param.ownerId));

      newFixtureGroups << newFixtureGroup;
    }

    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    fixtureGroupCrud.save(newFixtureGroups);
  }
};

template <template <typename> class Crud>
class Updater<FixtureGroup, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<FixtureGroupUpdateParameters>& params) {
    FixtureGroupSharedList fixtureGroups;

    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    Crud<FixtureGroupType> fixtureGroupTypeCrud;
    fixtureGroupTypeCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());

    for (const auto& param : params) {
      FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(param.groupId);
      fixtureGroup->setName(param.name);
      fixtureGroup->setType(fixtureGroupTypeCrud.selById(param.groupTypeId));
      fixtureGroup->setOwner(contragentCrud.selById(param.ownerId));

      fixtureGroups << fixtureGroup;
    }

    fixtureGroupCrud.save(fixtureGroups);
  }
};

template <template <typename> class Crud>
class DeleterFromList<FixtureGroup, Crud> : public SessionOwner
{
public:
  void del(ID listId, const IDList& ids) {
    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(listId);
    for (ID id : ids) {
      fixtureGroup->removeFixture(id);
    }
    fixtureGroupCrud.save({fixtureGroup});
  }
};

template <template <typename> class Crud>
class InserterToList<FixtureGroup, Crud> : public SessionOwner
{
public:
  void add(ID listId, const IDList& ids) {
    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(listId);

    Crud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    for (auto id : ids) {
      auto fixture = fixtureCrud.selById(id);
      fixtureGroup->addFixture(fixture);
    }
    fixtureGroupCrud.save({fixtureGroup});
  }
};

} // namespace light

#endif // FIXTUREGROUPCONTROLLER_H
