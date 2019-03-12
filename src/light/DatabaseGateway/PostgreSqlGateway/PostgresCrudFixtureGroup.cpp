#include "PostgresCrudFixtureGroup.h"

#include "DeleteQuery.h"
#include "Fixture.h"
#include "InsertQuery.h"
#include "UpdateQuery.h"

#include <QElapsedTimer>
#include <QSet>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

namespace light {
namespace PostgresqlGateway {

FixtureSharedList selectFixtures(const FixtureGroupShared & fixtureGroup, const SessionShared & session) {
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
  SelectQuery selectFixtureIds(session->getDb());
  selectFixtureIds.prepare(selectAllFixtureIdSql);
  selectFixtureIds.bind(bindParamsSelectAllId);
  selectFixtureIds.exec();
  PostgresCrud<Fixture> fixtureCrud;
  fixtureCrud.setSession(session);
  FixtureSharedList fixtures;
  for (auto record : selectFixtureIds) {
    auto fixtureId = record.value(0).value<ID>();
    fixtures << fixtureCrud.selById(fixtureId);
  }
  return fixtures;
}

template <>
template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel<ID, ID>(ID ownerId, ID typeId) const {
  FixtureGroupSharedList result;
  const QString sql = "select id_fixture_group, id_fixture_group_type, id_owner, id_geograph, name_fixture_group, "
		      "n_coordinate, e_coordinate "
		      "from fixture_group_pkg_i.fixture_group_vwf(:id_owner, :id_fixture_group_type) ";
  const BindParamsType bindParams{
      {":id_owner", ownerId ? ownerId : QVariant()},
      {":id_fixture_group_type", typeId ? typeId : QVariant()},
  };
  result << selBase(sql, bindParams);

  for (auto fixtureGroup : result) {
    fixtureGroup->setFixtures(selectFixtures(fixtureGroup, session));
  }

  return result;
}

template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel(const IDList& ids) const {
  FixtureGroupSharedList result;
  const QString sql = "select id_fixture_group, id_fixture_group_type, id_owner, id_geograph, name_fixture_group, "
		      "n_coordinate, e_coordinate "
		      "from fixture_group_pkg_i.fixture_group_vwf(:id_owner, :id_fixture_group_type) "
		      "where id_fixture_group = :id_fixture_group";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_owner", QVariant()},
	{":id_fixture_group_type", QVariant()},
	{":id_fixture_group", id},
    };
    result << selBase(sql, bindParams);
  }
  for (auto fixtureGroup : result) {
    for (auto fixtureGroup : result) {
      fixtureGroup->setFixtures(selectFixtures(fixtureGroup, session));
    }
  }
  return result;
}

template <>
void PostgresCrud<FixtureGroup>::ins(const FixtureGroupShared& fixtureGroup) const {
  const QString saveSql =
      "select fixture_group_pkg_i.save(:action, :id_fixture_group, :id_fixture_group_type, :id_owner, "
      ":name_fixture_group)";
  BindParamsType bindParams{
      {":action", "ins"},
      {":id_fixture_group", QVariant()},
      {":id_fixture_group_type", fixtureGroup->getTypeId() ? fixtureGroup->getTypeId() : QVariant()},
      {":id_owner", fixtureGroup->getOwnerId() ? fixtureGroup->getOwnerId() : QVariant()},
      {":name_fixture_group", fixtureGroup->getName()},
  };
  auto query = buildAndExecQuery<InsertQuery>(saveSql, bindParams, session);
  auto groupId = query.getInsertedId();

  const QString saveItemSql = "select fixture_pkg_i.ins_fixture_in_group(:id_fixture_group, :id_fixture)";
  InsertQuery insertItemQuery(session->getDb());
  query.prepare(saveItemSql);
  for (auto fixture : fixtureGroup->getFixtures()) {
    insertItemQuery.bind({
	{":id_fixture_group", groupId},
	{":id_fixture", fixture->getId()},
    });
    insertItemQuery.exec();
    insertItemQuery.finish();
  }
}

QSet<ID> selectCurrentFixtureIds(const FixtureGroupShared & fixtureGroup, const SessionShared & session) {
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
  SelectQuery selectFixtureIds(session->getDb());
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

void deleteFixtureFromGroup(const QSet<ID> idsToDelete, const FixtureGroupShared & fixtureGroup, const SessionShared & session) {
  const QString deleteGroupItemsSql = "select fixture_pkg_i.del_fixture_in_group(:id_fixture_group, :id_fixture)";
  DeleteQuery deleteGroupItemQuery(session->getDb());
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

void insertNewFixtureToGroup(const QSet<ID> idsToInsert, const FixtureGroupShared & fixtureGroup, const SessionShared & session) {
  const QString saveItemSql = "select fixture_pkg_i.ins_fixture_in_group(:id_fixture_group, :id_fixture)";
  InsertQuery insertItemQuery(session->getDb());
  insertItemQuery.prepare(saveItemSql);
  for (auto id : idsToInsert) {
    const BindParamsType bindParamsInsertGroupItem {
	{":id_fixture_group", fixtureGroup->getId()},
	{":id_fixture", id},
    };
    insertItemQuery.bind(bindParamsInsertGroupItem);
    insertItemQuery.exec();
    insertItemQuery.finish();
  }
}

template <>
void PostgresCrud<FixtureGroup>::upd(const FixtureGroupShared& fixtureGroup) const {
  const QString saveSql =
      "select fixture_group_pkg_i.save(:action, :id_fixture_group, :id_fixture_group_type, :id_owner, "
      ":name_fixture_group)";
  const BindParamsType bindParams{
      {":action", "upd"},
      {":id_fixture_group", fixtureGroup->getId()},
      {":id_fixture_group_type", fixtureGroup->getTypeId() ? fixtureGroup->getTypeId() : QVariant()},
      {":id_owner", fixtureGroup->getOwnerId() ? fixtureGroup->getOwnerId() : QVariant()},
      {":name_fixture_group", fixtureGroup->getName()},
  };
  auto query = buildAndExecQuery<UpdateQuery>(saveSql, bindParams, session);

  auto fixtures = fixtureGroup->getFixtures();
  QSet<ID> currentIds;
  for (auto fixture : fixtures) {
    currentIds << fixture->getId();
  }

  QSet<ID> dbIds = selectCurrentFixtureIds(fixtureGroup, session);
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteFixtureFromGroup(idsToDelete, fixtureGroup, session);
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertNewFixtureToGroup(idsToInsert, fixtureGroup, session);
  }
}

template <>
void PostgresCrud<FixtureGroup>::del(const FixtureGroupSharedList& fixtureGroups) const {
  const QString deleteSql = "select fixture_group_pkg_i.del(:id)";
  QVariantList bindIds;
  std::transform(fixtureGroups.begin(),
		 fixtureGroups.end(),
		 std::back_inserter(bindIds),
		 [](const FixtureGroupShared& fixtureGroup) { return QVariant(fixtureGroup->getId()); });
  BindParamsType bindParams{
      {":id", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteSql, bindParams, session);
}

template <>
FixtureGroupShared PostgresCrud<FixtureGroup>::parse(const QSqlRecord& record) const {
  auto fixtureGroup = FixtureGroupShared::create();
  fixtureGroup->setId(record.value(0).value<ID>());

  auto idType = record.value(1).value<ID>();

  PostgresCrud<FixtureGroupType> typeCrud;
  typeCrud.setSession(session);
  fixtureGroup->setType(typeCrud.selById(idType));

  auto ownerId = record.value(2).value<ID>();
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setSession(session);
  fixtureGroup->setOwner(contragentCrud.selById(ownerId));

  auto geographId = record.value(3).value<ID>();
  PostgresCrud<Geograph> geographCrud;
  geographCrud.setSession(session);
  fixtureGroup->setGeograph(geographCrud.selById(geographId));

  auto name = record.value(4).toString();
  fixtureGroup->setName(name);
  fixtureGroup->setCoordinate(record.value(5).toDouble(), record.value(6).toDouble());

  return fixtureGroup;
}

} // namespace PostgresqlGateway
} // namespace light
