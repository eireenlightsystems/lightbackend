#include "PostgresCrudFixture.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "UpdateQuery.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
FixtureSharedList PostgresCrud<Fixture>::sel<ID, ID, ID, ID, ID, ID, ID>(ID geographId,
									 ID ownerId,
									 ID fixtureTypeId,
									 ID substationId,
									 ID modeId,
									 ID contractId,
									 ID nodeId) const {
  FixtureSharedList result;
  const QString sql =
      "select id_fixture, id_contract, id_fixture_type, id_installer, id_substation, "
      "id_height_type, id_owner, id_node, work_level, standby_level, speed_zero_to_full, speed_full_to_zero, comments "
      "from fixture_pkg_i.fixture_vwf(:id_geograph, :id_owner, :id_fixture_type, :id_substation, :id_mode, "
      ":id_contract, "
      ":id_node)";
  const BindParamsType bindParams{
      {":id_geograph", idToVariant(geographId)},
      {":id_owner", idToVariant(ownerId)},
      {":id_fixture_type", idToVariant(fixtureTypeId)},
      {":id_substation", idToVariant(substationId)},
      {":id_mode", idToVariant(modeId)},
      {":id_contract", idToVariant(contractId)},
      {":id_node", idToVariant(nodeId)},
  };
  result << selBase(sql, bindParams);
  return result;
}

template <>
FixtureSharedList PostgresCrud<Fixture>::sel(const IDList& ids) const {
  FixtureSharedList result;
  const QString sql =
      "select id_fixture, id_contract, id_fixture_type, id_installer, id_substation, "
      "id_height_type, id_owner, id_node, work_level, standby_level, speed_zero_to_full, speed_full_to_zero, comments "
      "from fixture_pkg_i.fixture_vwf(null,null,null,null,null,null,null) "
      "where id_fixture = :id_fixture";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_fixture", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
void PostgresCrud<Fixture>::ins(const FixtureShared& fixture) const {
  const QString saveSql = "select fixture_pkg_i.save(:action, :id_fixture, :id_contract, :id_equipment_type, "
			  ":id_geograph, :id_installer, :id_substation, :id_height_type, :id_node, :numline, :side, "
			  ":flg_chief, :price, :comments)";
  BindParamsType bindParams{
      {":action", "ins"},
      {":id_fixture", QVariant()},
      {":id_contract", idToVariant(fixture->getContractId())},
      {":id_equipment_type", idToVariant(fixture->getTypeId())},
      {":id_geograph", idToVariant(fixture->getGeographId())},
      {":id_installer", idToVariant(fixture->getInstallerId())},
      {":id_substation", idToVariant(fixture->getSubstationId())},
      {":id_height_type", idToVariant(fixture->getHeightTypeId())},
      {":id_node", idToVariant(fixture->getNodeId())},
      {":numline", 1},

      {":side", "r"},
      {":flg_chief", false},
      {":price", fixture->getPrice()},
      {":comments", fixture->getComment()},
  };
  auto query = buildAndExecQuery<InsertQuery>(saveSql, bindParams, session);
}

template <>
void PostgresCrud<Fixture>::upd(const FixtureShared& fixture) const {
  const QString saveSql = "select fixture_pkg_i.save(:action, :id_fixture, :id_contract, :id_equipment_type, "
			  ":id_geograph, :id_installer, :id_substation, :id_height_type, :id_node, :numline, :side, "
			  ":flg_chief, :price, :comments)";
  BindParamsType bindParams{
      {":action", "upd"},
      {":id_fixture", idToVariant(fixture->getId())},
      {":id_contract", idToVariant(fixture->getContractId())},
      {":id_equipment_type", idToVariant(fixture->getTypeId())},
      {":id_geograph", idToVariant(fixture->getGeographId())},
      {":id_installer", idToVariant(fixture->getInstallerId())},
      {":id_substation", idToVariant(fixture->getSubstationId())},
      {":id_height_type", idToVariant(fixture->getHeightTypeId())},
      {":id_node", idToVariant(fixture->getNodeId())},
      {":numline", 1},
      {":side", "r"},
      {":flg_chief", false},
      {":price", fixture->getPrice()},
      {":comments", fixture->getComment()},
  };
  auto query = buildAndExecQuery<UpdateQuery>(saveSql, bindParams, session);
}

template <>
void PostgresCrud<Fixture>::del(const FixtureSharedList& fixtures) const {
  const QString deleteSql = "select fixture_pkg_i.del(:id)";
  QVariantList bindIds;
  std::transform(fixtures.begin(), fixtures.end(), std::back_inserter(bindIds), [](const FixtureShared& fixture) {
    return QVariant(fixture->getId());
  });
  BindParamsType bindParams{
      {":id", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteSql, bindParams, session);
}

template <>
FixtureShared PostgresCrud<Fixture>::parse(const QSqlRecord& record) const {
  auto fixture = FixtureShared::create();
  fixture->setId(record.value(0).value<ID>());

  auto contractId = record.value(1).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(session);
  fixture->setContract(contractCrud.selById(contractId));

  auto typeId = record.value(2).value<ID>();
  PostgresCrud<FixtureType> typeCrud;
  typeCrud.setSession(session);
  fixture->setType(typeCrud.selById(typeId));

  auto installerId = record.value(3).value<ID>();
  PostgresCrud<Contragent> installerCrud;
  installerCrud.setSession(session);
  fixture->setInstaller(installerCrud.selById(installerId));

  auto substationId = record.value(4).value<ID>();
  PostgresCrud<Substation> substationCrud;
  substationCrud.setSession(session);
  fixture->setInstaller(installerCrud.selById(substationId));

  auto heightTypeId = record.value(5).value<ID>();
  PostgresCrud<FixtureHeightType> heightTypeCrud;
  heightTypeCrud.setSession(session);
  fixture->setHeightType(heightTypeCrud.selById(heightTypeId));

  auto ownerId = record.value(6).value<ID>();
  PostgresCrud<Contragent> ownerCrud;
  ownerCrud.setSession(session);
  fixture->setOwner(ownerCrud.selById(ownerId));

  auto nodeId = record.value(7).value<ID>();
  PostgresCrud<Node> nodeCrud;
  nodeCrud.setSession(session);
  fixture->setNode(nodeCrud.selById(nodeId));

  fixture->setWorkLevel(record.value(8).value<quint8>());
  fixture->setStandbyLevel(record.value(9).value<quint8>());
  fixture->setSpeedUp(record.value(10).value<quint8>());
  fixture->setSpeedDown(record.value(11).value<quint8>());
  fixture->setComment(record.value(12).toString());

  return fixture;
}

} // namespace PostgresqlGateway
} // namespace light
