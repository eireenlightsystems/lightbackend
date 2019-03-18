#include "PostgresCrudFixtureGroup.h"

#include "DeleteQuery.h"
#include "Fixture.h"
#include "InsertQuery.h"
#include "PostgresCrudContragent.h"
#include "PostgresCrudFixture.h"
#include "PostgresCrudFixtureGroupType.h"
#include "PostgresCrudGeograph.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSet>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureGroupFields{
    {"id_fixture_group", "id_fixture_group", true},
    {"name_fixture_group", "name_fixture_group", false},
    {"n_coordinate", "n_coordinate", false},
    {"e_coordinate", "e_coordinate", false},

    {"id_fixture_group_type", "id_fixture_group_type", false},
    {"name_fixture_group_type", "name_fixture_group_type", false},

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},
};

PostgresCrud<FixtureGroup>::PostgresCrud() {
  setFields(fixtureGroupFields);
  setView("fixture_group_pkg_i.fixture_group_vwf(:id_owner, :id_fixture_group_type)");
  setInsertSql("select fixture_group_pkg_i.save(:action, :id_fixture_group, :id_fixture_group_type, :id_owner, "
	       ":name_fixture_group)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select fixture_group_pkg_i.del(:id)");
}

Editor<FixtureGroup>::Shared PostgresCrud<FixtureGroup>::parse(const QSqlRecord& record) const {
  auto fixtureGroup = FixtureGroupShared::create();
  fixtureGroup->setId(record.value(getIdAlias()).value<ID>());

  PostgresCrud<FixtureGroupType> typeCrud;
  typeCrud.setSession(getSession());
  fixtureGroup->setType(typeCrud.parse(record));

  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setSession(getSession());
  contragentCrud.setFields({
      {"id_contragent", "id_owner", true},
      {"code_contragent", "code_owner", false},
  });
  fixtureGroup->setOwner(contragentCrud.parse(record));

  PostgresCrud<Geograph> geographCrud;
  geographCrud.setSession(getSession());
  fixtureGroup->setGeograph(geographCrud.parse(record));

  auto name = record.value(getFiledAlias("name_fixture_group")).toString();
  fixtureGroup->setName(name);
  fixtureGroup->setCoordinate(record.value(getFiledAlias("n_coordinate")).toDouble(),
			      record.value(getFiledAlias("e_coordinate")).toDouble());

  return fixtureGroup;
}

BindParamsType PostgresCrud<FixtureGroup>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_owner", filters.value("ownerId")},
      {":id_fixture_group_type", filters.value("fixtureGroupTypeId")},
  };
}

BindParamsType PostgresCrud<FixtureGroup>::getInsertParams(const Editor::Shared& fixtureGroup) const {
  return BindParamsType{
      {":action", "ins"},
      {":id_fixture_group", QVariant()},
      {":id_fixture_group_type", fixtureGroup->getTypeId() ? fixtureGroup->getTypeId() : QVariant()},
      {":id_owner", fixtureGroup->getOwnerId() ? fixtureGroup->getOwnerId() : QVariant()},
      {":name_fixture_group", fixtureGroup->getName()},
  };
}

BindParamsType PostgresCrud<FixtureGroup>::getUpdateParams(const Editor::Shared& fixtureGroup) const {
  return BindParamsType{
      {":action", "upd"},
      {":id_fixture_group", fixtureGroup->getId()},
      {":id_fixture_group_type", fixtureGroup->getTypeId() ? fixtureGroup->getTypeId() : QVariant()},
      {":id_owner", fixtureGroup->getOwnerId() ? fixtureGroup->getOwnerId() : QVariant()},
      {":name_fixture_group", fixtureGroup->getName()},
  };
}

void PostgresCrud<FixtureGroup>::ins(const Editor::Shared& fixtureGroup) const {
  Editor<FixtureGroup>::ins(fixtureGroup);

  const QString saveItemSql = "select fixture_pkg_i.ins_fixture_in_group(:id_fixture_group, :id_fixture)";
  InsertQuery insertItemQuery(getSession()->getDb());
  insertItemQuery.prepare(saveItemSql);
  for (auto fixture : fixtureGroup->getFixtures()) {
    insertItemQuery.bind({
	{":id_fixture_group", fixtureGroup->getId()},
	{":id_fixture", fixture->getId()},
    });
    insertItemQuery.exec();
    insertItemQuery.finish();
  }
}

void PostgresCrud<FixtureGroup>::upd(const Editor::Shared& fixtureGroup) const {
  Editor<FixtureGroup>::upd(fixtureGroup);

  auto fixtures = fixtureGroup->getFixtures();
  QSet<ID> currentIds;
  for (auto fixture : fixtures) {
    currentIds << fixture->getId();
  }

  QSet<ID> dbIds = selectCurrentFixtureIds(fixtureGroup);
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteFixtureFromGroup(idsToDelete, fixtureGroup);
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertNewFixtureToGroup(idsToInsert, fixtureGroup);
  }
}

Editor<FixtureGroup>::SharedList PostgresCrud<FixtureGroup>::sel(const IDList& ids) const {
  auto result = Editor<FixtureGroup>::sel(ids);
  for (auto fixtureGroup : result) {
    fixtureGroup->setFixtures(selectFixtures(fixtureGroup));
  }
  return result;
}

Editor<FixtureGroup>::SharedList PostgresCrud<FixtureGroup>::sel(const QVariantHash& filters) const {
  auto result = Editor<FixtureGroup>::sel(filters);
  for (auto fixtureGroup : result) {
    fixtureGroup->setFixtures(selectFixtures(fixtureGroup));
  }
  return result;
}

FixtureSharedList PostgresCrud<FixtureGroup>::selectFixtures(const FixtureGroupShared& fixtureGroup) const {
  const QString selectAllFixtureIdSql =
      "select id_fixture from fixture_pkg_i.fixture_in_group_vwf(:id_geograph, "
      ":id_owner, :id_fixture_type, :id_substation, :flg_light, :id_contract, :id_node, :id_fixture_group)";
  const BindParamsType bindParamsSelectAllId{
      {":id_geograph", QVariant()},
      {":id_owner", QVariant()},
      {":id_fixture_type", QVariant()},
      {":id_substation", QVariant()},
      {":flg_light", QVariant()},
      {":id_contract", QVariant()},
      {":id_node", QVariant()},
      {":id_fixture_group", fixtureGroup->getId()},
  };
  SelectQuery selectFixtureIds(getSession()->getDb());
  selectFixtureIds.prepare(selectAllFixtureIdSql);
  selectFixtureIds.bind(bindParamsSelectAllId);
  selectFixtureIds.exec();
  PostgresCrud<Fixture> fixtureCrud;
  fixtureCrud.setSession(getSession());
  FixtureSharedList fixtures;
  for (auto record : selectFixtureIds) {
    auto fixtureId = record.value(0).value<ID>();
    fixtures << fixtureCrud.selById(fixtureId);
  }
  return fixtures;
}

QSet<ID> PostgresCrud<FixtureGroup>::selectCurrentFixtureIds(const FixtureGroupShared& fixtureGroup) const {
  const QString selectAllFixtureIdSql =
      "select id_fixture from fixture_pkg_i.fixture_in_group_vwf(:id_geograph, "
      ":id_owner, :id_fixture_type, :id_substation, :flg_light, :id_contract, :id_node, :id_fixture_group)";
  const BindParamsType bindParamsSelectAllId{
      {":id_geograph", QVariant()},
      {":id_owner", QVariant()},
      {":id_fixture_type", QVariant()},
      {":id_substation", QVariant()},
      {":flg_light", QVariant()},
      {":id_contract", QVariant()},
      {":id_node", QVariant()},
      {":id_fixture_group", fixtureGroup->getId()},
  };
  SelectQuery selectFixtureIds(getSession()->getDb());
  selectFixtureIds.prepare(selectAllFixtureIdSql);
  selectFixtureIds.bind(bindParamsSelectAllId);
  selectFixtureIds.exec();
  QSet<ID> dbIds;
  for (auto record : selectFixtureIds) {
    auto id = record.value(0).value<ID>();
    dbIds << id;
  }
  return dbIds;
}

void PostgresCrud<FixtureGroup>::insertNewFixtureToGroup(const QSet<ID> idsToInsert,
							 const FixtureGroupShared& fixtureGroup) const {
  const QString saveItemSql = "select fixture_pkg_i.ins_fixture_in_group(:id_fixture_group, :id_fixture)";
  InsertQuery insertItemQuery(getSession()->getDb());
  insertItemQuery.prepare(saveItemSql);
  for (auto id : idsToInsert) {
    const BindParamsType bindParamsInsertGroupItem{
	{":id_fixture_group", fixtureGroup->getId()},
	{":id_fixture", id},
    };
    insertItemQuery.bind(bindParamsInsertGroupItem);
    insertItemQuery.exec();
    insertItemQuery.finish();
  }
}

void PostgresCrud<FixtureGroup>::deleteFixtureFromGroup(const QSet<ID> idsToDelete,
							const FixtureGroupShared& fixtureGroup) const {
  const QString deleteGroupItemsSql = "select fixture_pkg_i.del_fixture_in_group(:id_fixture_group, :id_fixture)";
  DeleteQuery deleteGroupItemQuery(getSession()->getDb());
  deleteGroupItemQuery.prepare(deleteGroupItemsSql);
  for (auto id : idsToDelete) {
    const BindParamsType bindParamsDeleteGroupItem{
	{":id_fixture", id},
	{":id_fixture_group", fixtureGroup->getId()},
    };
    deleteGroupItemQuery.bind(bindParamsDeleteGroupItem);
    deleteGroupItemQuery.exec();
    deleteGroupItemQuery.finish();
  }
}

} // namespace PostgresqlGateway
} // namespace light
