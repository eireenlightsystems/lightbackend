#ifndef FIXTUREGROUPCONTROLLER_H
#define FIXTUREGROUPCONTROLLER_H

#include "Controller.h"
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
    FixtureGroupSharedList newFixtureGroups;

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

      newFixtureGroups << fixtureGroup;
    }

    fixtureGroupCrud.save(newFixtureGroups);
  }
};

} // namespace light

#endif // FIXTUREGROUPCONTROLLER_H
