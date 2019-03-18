#ifndef FIXTUREGROUPCONTROLLER_H
#define FIXTUREGROUPCONTROLLER_H

#include "Controller.h"
#include "Fixture.h"
#include "FixtureGroup.h"

#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Controller<FixtureGroup, Crud> : public EditableListController<FixtureGroup, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
  void delFromList(ID listId, const IDList& ids) override;
  void addToList(ID listId, const IDList& ids) override;
};

template <template <typename> class Crud>
IDList Controller<FixtureGroup, Crud>::ins(const QList<QVariantHash>& params) {
  FixtureGroupSharedList newFixtureGroups;

  Crud<FixtureGroupType> fixtureGroupTypeCrud;
  fixtureGroupTypeCrud.setSession(this->getSession());
  Crud<Contragent> contragentCrud;
  contragentCrud.setSession(this->getSession());

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
  fixtureGroupCrud.setSession(this->getSession());
  fixtureGroupCrud.save(newFixtureGroups);
  IDList result;
  std::transform(newFixtureGroups.begin(),
		 newFixtureGroups.end(),
		 std::back_inserter(result),
		 [](const FixtureGroupShared& fixtureGroup) { return fixtureGroup->getId(); });
  return result;
}

template <template <typename> class Crud>
void Controller<FixtureGroup, Crud>::upd(const QList<QVariantHash>& params) {
  FixtureGroupSharedList fixtureGroups;

  Crud<FixtureGroup> fixtureGroupCrud;
  fixtureGroupCrud.setSession(this->getSession());
  Crud<FixtureGroupType> fixtureGroupTypeCrud;
  fixtureGroupTypeCrud.setSession(this->getSession());
  Crud<Contragent> contragentCrud;
  contragentCrud.setSession(this->getSession());

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

template <template <typename> class Crud>
void Controller<FixtureGroup, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["fixtureGroupId"] = id;
  return upd({fullParam});
}

template <template <typename> class Crud>
void Controller<FixtureGroup, Crud>::delFromList(ID listId, const IDList& ids) {
  Crud<FixtureGroup> fixtureGroupCrud;
  fixtureGroupCrud.setSession(this->getSession());
  FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(listId);
  for (ID id : ids) {
    fixtureGroup->removeFixture(id);
  }
  fixtureGroupCrud.save({fixtureGroup});
}

template <template <typename> class Crud>
void Controller<FixtureGroup, Crud>::addToList(ID listId, const IDList& ids) {
  Crud<FixtureGroup> fixtureGroupCrud;
  fixtureGroupCrud.setSession(this->getSession());
  FixtureGroupShared fixtureGroup = fixtureGroupCrud.selById(listId);

  Crud<Fixture> fixtureCrud;
  fixtureCrud.setSession(this->getSession());
  for (auto id : ids) {
    auto fixture = fixtureCrud.selById(id);
    fixtureGroup->addFixture(fixture);
  }
  fixtureGroupCrud.save({fixtureGroup});
}

} // namespace light

#endif // FIXTUREGROUPCONTROLLER_H
