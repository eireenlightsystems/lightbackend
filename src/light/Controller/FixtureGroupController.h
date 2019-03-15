#ifndef FIXTUREGROUPCONTROLLER_H
#define FIXTUREGROUPCONTROLLER_H

#include "Controller.h"
#include "Fixture.h"
#include "FixtureGroup.h"

#include <QVariant>

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
  IDList ins(const QList<QVariantHash>& params) {
    FixtureGroupSharedList newFixtureGroups;

    Crud<FixtureGroupType> fixtureGroupTypeCrud;
    fixtureGroupTypeCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());

    for (const auto& param : params) {
      auto newFixtureGroup = FixtureGroupShared::create();
      if (param.contains("fixtureGroupName")) {

	QString name = param.value("fixtureGroupName").toString();
	newFixtureGroup->setName(name);
      }

      if (param.contains("fixtureGroupTypeId")) {
	ID groupTypeId = param.value("fixtureGroupTypeId").value<ID>();
	auto fixtureGroupType = fixtureGroupTypeCrud.selById(groupTypeId);
	newFixtureGroup->setType(fixtureGroupType);
      }

      if (param.contains("ownerId")) {
	ID ownerId = param.value("ownerId").value<ID>();
	auto contragent = contragentCrud.selById(ownerId);
	newFixtureGroup->setOwner(contragent);
      }

      newFixtureGroups << newFixtureGroup;
    }

    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    fixtureGroupCrud.save(newFixtureGroups);
    IDList result;
    std::transform(newFixtureGroups.begin(),
		   newFixtureGroups.end(),
		   std::back_inserter(result),
		   [](const FixtureGroupShared& fixtureGroup) { return fixtureGroup->getId(); });
    return result;
  }
};

template <template <typename> class Crud>
class Updater<FixtureGroup, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<QVariantHash>& params) {
    FixtureGroupSharedList fixtureGroups;

    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    Crud<FixtureGroupType> fixtureGroupTypeCrud;
    fixtureGroupTypeCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());

    for (const auto& param : params) {
      ID groupId = param.value("fixtureGroupId").value<ID>();
      FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(groupId);
      if (param.contains("fixtureGroupName")) {
	QString name = param.value("fixtureGroupName").toString();
	fixtureGroup->setName(name);
      }

      if (param.contains("fixtureGroupTypeId")) {
	ID groupTypeId = param.value("fixtureGroupTypeId").value<ID>();
	auto fixtureGroupType = fixtureGroupTypeCrud.selById(groupTypeId);
	fixtureGroup->setType(fixtureGroupType);
      }

      if (param.contains("ownerId")) {
	ID ownerId = param.value("ownerId").value<ID>();
	auto contragent = contragentCrud.selById(ownerId);
	fixtureGroup->setOwner(contragent);
      }

      fixtureGroups << fixtureGroup;
    }

    fixtureGroupCrud.save(fixtureGroups);
  }

  void upd(ID id, const QVariantHash& param) {
    Crud<FixtureGroup> fixtureGroupCrud;
    fixtureGroupCrud.setSession(getSession());
    Crud<FixtureGroupType> fixtureGroupTypeCrud;
    fixtureGroupTypeCrud.setSession(getSession());
    Crud<Contragent> contragentCrud;
    contragentCrud.setSession(getSession());

    FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(id);
    if (param.contains("fixtureGroupName")) {
      QString name = param.value("fixtureGroupName").toString();
      fixtureGroup->setName(name);
    }

    if (param.contains("fixtureGroupTypeId")) {
      ID groupTypeId = param.value("fixtureGroupTypeId").value<ID>();
      auto fixtureGroupType = fixtureGroupTypeCrud.selById(groupTypeId);
      fixtureGroup->setType(fixtureGroupType);
    }

    if (param.contains("ownerId")) {
      ID ownerId = param.value("ownerId").value<ID>();
      auto contragent = contragentCrud.selById(ownerId);
      fixtureGroup->setOwner(contragent);
    }
    fixtureGroupCrud.save({fixtureGroup});
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
