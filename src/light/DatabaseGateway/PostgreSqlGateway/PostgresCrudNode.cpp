#include "PostgresCrudNode.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudFixture.h"
#include "PostgresCrudGateway.h"
#include "PostgresCrudGeograph.h"
#include "PostgresCrudNodeType.h"
#include "PostgresCrudSensor.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> nodeFields{
    {"id_node", "id_node", true},
    {"n_coordinate", "n_coordinate_node", false},
    {"e_coordinate", "e_coordinate_node", false},
    {"comments", "comments_node", false},
    {"serial_number", "serial_number_node", false},

    {"id_node_type", "id_node_type", false},
    {"code_node_type", "code_node_type", false},

    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},
};

PostgresCrud<Node>::PostgresCrud() {
  setFields(nodeFields);
  setView("node_pkg_i.node_vwf(:id_geograph, :id_owner, :id_node_type, :id_contract, :id_gateway)");
  setInsertSql("select node_pkg_i.save(:action, :id_node, :id_contract, :id_equipment_type, "
	       ":id_geograph, :n_coordinate, :e_coordinate, :comments, :serial_number)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select node_pkg_i.del(:id)");
}

Editor<Node>::Shared PostgresCrud<Node>::parse(const QSqlRecord& record) const {
  auto node = NodeShared::create();
  node->setId(record.value(getIdAlias()).value<ID>());
  node->setCoordinate(record.value(getFieldAlias("n_coordinate")).toDouble(),
		      record.value(getFieldAlias("e_coordinate")).toDouble());
  node->setComment(record.value(getFieldAlias("comments")).toString());
  node->setSerialNumber(record.value(getFieldAlias("serial_number")).toString());

  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  node->setOwner(equipmentOwnerCrud.parse(record));

  PostgresCrud<Contract> contractCrud;
  node->setContract(contractCrud.parse(record));

  PostgresCrud<Geograph> geographCrud;
  node->setGeograph(geographCrud.parse(record));

  PostgresCrud<NodeType> nodeTypeCrud;
  node->setNodeType(nodeTypeCrud.parse(record));

  if (getLoadChildren() and getSession()) {
    QVariantHash params{
	{"nodeId", node->getId()},
    };
    PostgresCrud<Sensor> sensorCrud;
    sensorCrud.setSession(getSession());
    sensorCrud.setLoadChildren(false);
    node->setSensors(sensorCrud.sel(params));

    PostgresCrud<Fixture> fixtureCrud;
    fixtureCrud.setSession(getSession());
    fixtureCrud.setLoadChildren(false);
    node->setFixtures(fixtureCrud.sel(params));

    PostgresCrud<Gateway> gatewayCrud;
    gatewayCrud.setSession(getSession());
    gatewayCrud.setLoadChildren(false);
    node->setGateways(gatewayCrud.sel(params));
  }

  return node;
}

BindParamsType PostgresCrud<Node>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_geograph", filters.value("geopraphId")},
      {":id_owner", filters.value("ownerId")},
      {":id_node_type", filters.value("nodeTypeId")},
      {":id_contract", filters.value("contractId")},
      {":id_gateway", filters.value("gatewayId")},
  };
}

BindParamsType PostgresCrud<Node>::getInsertParams(const Editor::Shared& node) const {
  return BindParamsType{
      {":action", "ins"},
      {":id_node", QVariant()},
      {":id_contract", idToVariant(node->getContractId())},
      {":id_equipment_type", idToVariant(node->getNodeTypeId())},
      {":id_geograph", idToVariant(node->getGeographId())},
      {":n_coordinate", node->getLatitude()},
      {":e_coordinate", node->getLongitude()},
      {":comments", node->getComment()},
      {":serial_number", node->getSerialNumber()},
  };
}

BindParamsType PostgresCrud<Node>::getUpdateParams(const Editor::Shared& node) const {
  return BindParamsType{
      {":action", "upd"},
      {":id_node", node->getId()},
      {":id_contract", idToVariant(node->getContractId())},
      {":id_equipment_type", idToVariant(node->getNodeTypeId())},
      {":id_geograph", idToVariant(node->getGeographId())},
      {":n_coordinate", node->getLatitude()},
      {":e_coordinate", node->getLongitude()},
      {":comments", node->getComment()},
      {":serial_number", node->getSerialNumber()},
  };
}

void PostgresCrud<Node>::ins(const Editor::Shared& node) const {
  Editor<Node>::ins(node);
}

void PostgresCrud<Node>::upd(const Editor::Shared& node) const {
  Editor<Node>::upd(node);
}

void PostgresCrud<Node>::saveChildren() {
  saveFixtures();
  saveGateways();
  saveSensors();
}

void PostgresCrud<Node>::saveFixtures() {
}

void PostgresCrud<Node>::insertFixtures() {
}

void PostgresCrud<Node>::deleteFixtures() {
}

void PostgresCrud<Node>::saveGateways() {
}

void PostgresCrud<Node>::insertGateways() {
}

void PostgresCrud<Node>::deleteGateways() {
}

void PostgresCrud<Node>::saveSensors() {
}

void PostgresCrud<Node>::insertSensors() {
}

void PostgresCrud<Node>::deleteSensors() {
}

} // namespace PostgresqlGateway
} // namespace light
