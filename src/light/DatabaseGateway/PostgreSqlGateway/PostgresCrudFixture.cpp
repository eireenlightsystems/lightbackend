#include "PostgresCrudFixture.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudContragent.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudFixtureHeightType.h"
#include "PostgresCrudFixtureType.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudSubstation.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureFields{
    {"id_fixture", "id_fixture", true},
    {"work_level", "work_level", false},
    {"standby_level", "standby_level", false},
    {"speed_zero_to_full", "speed_zero_to_full", false},
    {"speed_full_to_zero", "speed_full_to_zero", false},
    {"comments", "comments", false},
    {"serial_number", "serial_number", false},

    {"id_fixture_type", "id_fixture_type", false},
    {"code_fixture_type", "code_fixture_type", false},
    {"model_fixture_type", "model_fixture_type", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},

    {"id_installer", "id_installer", false},
    {"code_installer", "code_installer", false},

    {"id_substation", "id_substation", false},
    {"code_substation", "code_substation", false},

    {"id_height_type", "id_height_type", false},
    {"code_height_type", "code_height_type", false},

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_node", "id_node", false},
    {"n_coordinate", "n_coordinate_node", false},
    {"e_coordinate", "e_coordinate_node", false},
    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},
};

PostgresCrud<Fixture>::PostgresCrud() {
  setFields(fixtureFields);
  setView("fixture_pkg_i.fixture_vwf(:id_geograph, :id_owner, :id_fixture_type, :id_substation, :id_mode, "
	  ":id_contract, :id_node)");
  setInsertSql("select fixture_pkg_i.save(:action, :id_fixture, :id_contract, :id_equipment_type, "
	       ":id_installer, :id_substation, :id_height_type, :id_node, :serial_number, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select fixture_pkg_i.del(:id)");
}

Editor<Fixture>::Shared PostgresCrud<Fixture>::parse(const QSqlRecord& record) const {
  auto fixture = FixtureShared::create();
  fixture->setId(record.value(getIdAlias()).value<ID>());

  PostgresCrud<Contract> contractCrud;
  fixture->setContract(contractCrud.parse(record));

  PostgresCrud<FixtureType> typeCrud;
  fixture->setType(typeCrud.parse(record));

  PostgresCrud<Contragent> installerCrud;
  installerCrud.setFields({
      {"id_contragent", "id_installer", true},
      {"code", "code_installer", false},
  });
  fixture->setInstaller(installerCrud.parse(record));

  PostgresCrud<Substation> substationCrud;
  fixture->setSubstation(substationCrud.parse(record));

  PostgresCrud<FixtureHeightType> heightTypeCrud;
  fixture->setHeightType(heightTypeCrud.parse(record));

  PostgresCrud<EquipmentOwner> ownerCrud;
  fixture->setOwner(ownerCrud.parse(record));

  PostgresCrud<Node> nodeCrud;
  fixture->setNode(nodeCrud.parse(record));

  fixture->setWorkLevel(record.value(getFieldAlias("work_level")).value<quint8>());
  fixture->setStandbyLevel(record.value(getFieldAlias("standby_level")).value<quint8>());
  fixture->setSpeedUp(record.value(getFieldAlias("speed_zero_to_full")).value<quint8>());
  fixture->setSpeedDown(record.value(getFieldAlias("speed_full_to_zero")).value<quint8>());
  fixture->setComment(record.value(getFieldAlias("comments")).toString());
  fixture->setSerialNumber(record.value(getFieldAlias("serial_number")).toString());

  return fixture;
}

BindParamsType PostgresCrud<Fixture>::getInsertParams(const Editor::Shared& fixture) const {
  return BindParamsType{
      {":action", "ins"},
      {":id_fixture", QVariant()},
      {":id_contract", idToVariant(fixture->getContractId())},
      {":id_equipment_type", idToVariant(fixture->getTypeId())},
      {":id_installer", idToVariant(fixture->getInstallerId())},
      {":id_substation", idToVariant(fixture->getSubstationId())},
      {":id_height_type", idToVariant(fixture->getHeightTypeId())},
      {":id_node", idToVariant(fixture->getNodeId())},
      {":serial_number", fixture->getSerialNumber()},
      {":comments", fixture->getComment()},
  };
}

BindParamsType PostgresCrud<Fixture>::getUpdateParams(const Editor::Shared& fixture) const {
  return BindParamsType{
      {":action", "upd"},
      {":id_fixture", QVariant()},
      {":id_contract", idToVariant(fixture->getContractId())},
      {":id_equipment_type", idToVariant(fixture->getTypeId())},
      {":id_installer", idToVariant(fixture->getInstallerId())},
      {":id_substation", idToVariant(fixture->getSubstationId())},
      {":id_height_type", idToVariant(fixture->getHeightTypeId())},
      {":id_node", idToVariant(fixture->getNodeId())},
      {":serial_number", fixture->getSerialNumber()},
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

const QList<Field> fixtureContractFields{
    {"id_contract", "id_contract", true},
    {"code_contract", "code_contract", false},
    {"name_contract", "name_contract", false},
};

PostgresCrud<FixtureContract>::PostgresCrud() {
  setFields(fixtureContractFields);
  setView("fixture_pkg_i.contract_vw");
}

Reader<FixtureContract>::Shared PostgresCrud<FixtureContract>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contract> contractCrud;
  auto contract = contractCrud.parse(record);
  auto fixtureContract = FixtureContractShared::create(*contract);
  return fixtureContract;
}

const QList<Field> fixtureOwnerFields{
    {"id_owner", "id_owner", true},
    {"code_owner", "code_owner", false},
    {"name_owner", "name_owner", false},
};

PostgresCrud<FixtureOwner>::PostgresCrud() {
  setFields(fixtureOwnerFields);
  setView("fixture_pkg_i.owner_vw");
}

Reader<FixtureOwner>::Shared PostgresCrud<FixtureOwner>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setFields({
      {"id_contragent", "id_owner", true},
      {"code", "code_owner", false},
      {"name", "name_owner", false},
  });
  auto contragent = contragentCrud.parse(record);
  auto fixtureOwner = FixtureOwnerShared::create(*contragent);
  return fixtureOwner;
}

const QList<Field> fixtureInstallerFields{
    {"id_installer", "id_installer", true},
    {"code", "code_installer", false},
    {"name", "name_installer", false},
};

PostgresCrud<FixtureInstaller>::PostgresCrud() {
  setFields(fixtureInstallerFields);
  setView("fixture_pkg_i.installer_vw");
}

Reader<FixtureInstaller>::Shared PostgresCrud<FixtureInstaller>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setFields({
      {"id_contragent", "id_installer", true},
      {"code", "code_installer", false},
      {"name", "name_installer", false},
  });
  auto contragent = contragentCrud.parse(record);
  auto fixtureOwner = FixtureInstallerShared::create(*contragent);
  return fixtureOwner;
}

} // namespace PostgresqlGateway
} // namespace light
