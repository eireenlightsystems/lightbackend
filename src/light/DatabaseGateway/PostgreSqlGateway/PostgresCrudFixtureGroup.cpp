#include "PostgresCrudFixtureGroup.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel<ID, ID>(ID ownerId, ID typeId) const {
  FixtureGroupSharedList result;
  const QString sql = "select id_fixture_group, id_fixture_group_type, id_owner, id_geograph, name_fixture_group "
		      "from fixture_group_pkg_i.fixture_group_vwf(:id_owner, :id_fixture_group_type) ";
  const BindParamsType bindParams{
      {":id_owner", ownerId ? ownerId : QVariant()},
      {":id_fixture_group_type", typeId ? typeId : QVariant()},
  };
  result << selBase(sql, bindParams);

  return result;
}

template <>
FixtureGroupSharedList PostgresCrud<FixtureGroup>::sel(const IDList& ids) const {
  FixtureGroupSharedList result;
  const QString sql = "select id_fixture_group, id_fixture_group_type, id_owner, id_geograph, name_fixture_group "
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
}

template <>
void PostgresCrud<FixtureGroup>::upd(const FixtureGroupShared& fixtureGroup) const {
  const QString saveSql =
      "select fixture_group_pkg_i.save(:action, :id_fixture_group, :id_fixture_group_type, :id_owner, "
      ":name_fixture_group)";
  BindParamsType bindParams{
      {":action", "upd"},
      {":id_fixture_group", fixtureGroup->getId()},
      {":id_fixture_group_type", fixtureGroup->getTypeId() ? fixtureGroup->getTypeId() : QVariant()},
      {":id_owner", fixtureGroup->getOwnerId() ? fixtureGroup->getOwnerId() : QVariant()},
      {":name_fixture_group", fixtureGroup->getName()},
  };
  auto query = buildAndExecQuery<InsertQuery>(saveSql, bindParams, session);
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
  return fixtureGroup;
}

} // namespace PostgresqlGateway
} // namespace light
