#include "PostgresCrudFixture.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudContragent.h"
#include "PostgresCrudFixtureHeightType.h"
#include "PostgresCrudFixtureType.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudSubstation.h"
#include "UpdateQuery.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<Fixture>::PostgresCrud() {
  setIdField("id_fixture");
  setFields(QStringList() << getIdField() << "id_contract"
			  << "id_fixture_type"
			  << "id_installer"
			  << "id_substation"
			  << "id_height_type"
			  << "id_owner"
			  << "id_node"
			  << "work_level"
			  << "standby_level"
			  << "speed_zero_to_full"
			  << "speed_full_to_zero"
			  << "comments");
  setView("fixture_pkg_i.fixture_vwf(:id_geograph, :id_owner, :id_fixture_type, :id_substation, :id_mode, "
	  ":id_contract, :id_node)");
  setInsertSql("select fixture_pkg_i.save(:action, :id_fixture, :id_contract, :id_equipment_type, "
	       ":id_geograph, :id_installer, :id_substation, :id_height_type, :id_node, :numline, :side, "
	       ":flg_chief, :price, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select fixture_pkg_i.del(:id)");
}

Editor<Fixture>::Shared PostgresCrud<Fixture>::parse(const QSqlRecord& record) const {
  auto fixture = FixtureShared::create();
  fixture->setId(record.value(0).value<ID>());

  auto contractId = record.value(1).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(getSession());
  fixture->setContract(contractCrud.selById(contractId));

  auto typeId = record.value(2).value<ID>();
  PostgresCrud<FixtureType> typeCrud;
  typeCrud.setSession(getSession());
  fixture->setType(typeCrud.selById(typeId));

  auto installerId = record.value(3).value<ID>();
  PostgresCrud<Contragent> installerCrud;
  installerCrud.setSession(getSession());
  fixture->setInstaller(installerCrud.selById(installerId));

  auto substationId = record.value(4).value<ID>();
  PostgresCrud<Substation> substationCrud;
  substationCrud.setSession(getSession());
  fixture->setInstaller(installerCrud.selById(substationId));

  auto heightTypeId = record.value(5).value<ID>();
  PostgresCrud<FixtureHeightType> heightTypeCrud;
  heightTypeCrud.setSession(getSession());
  fixture->setHeightType(heightTypeCrud.selById(heightTypeId));

  auto ownerId = record.value(6).value<ID>();
  PostgresCrud<Contragent> ownerCrud;
  ownerCrud.setSession(getSession());
  fixture->setOwner(ownerCrud.selById(ownerId));

  auto nodeId = record.value(7).value<ID>();
  PostgresCrud<Node> nodeCrud;
  nodeCrud.setSession(getSession());
  fixture->setNode(nodeCrud.selById(nodeId));

  fixture->setWorkLevel(record.value(8).value<quint8>());
  fixture->setStandbyLevel(record.value(9).value<quint8>());
  fixture->setSpeedUp(record.value(10).value<quint8>());
  fixture->setSpeedDown(record.value(11).value<quint8>());
  fixture->setComment(record.value(12).toString());

  return fixture;
}

BindParamsType PostgresCrud<Fixture>::getInsertParams(const Editor::Shared& fixture) const {
  return BindParamsType{
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
}

BindParamsType PostgresCrud<Fixture>::getUpdateParams(const Editor::Shared& fixture) const {
  return BindParamsType{
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
}

BindParamsType PostgresCrud<Fixture>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_geograph", filters.value("geographId")},
      {":id_owner", filters.value("ownerId")},
      {":id_fixture_type", filters.value("fixtureTypeId")},
      {":id_substation", filters.value("substationId")},
      {":id_mode", filters.value("modeId")},
      {":id_contract", filters.value("contractId")},
      {":id_node", filters.value("nodeId")},
  };
}

} // namespace PostgresqlGateway
} // namespace light
