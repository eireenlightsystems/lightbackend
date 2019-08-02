#include "PostgresCrudNode.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudContragent.h"
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
    {"num_node", "num_node", false},

    {"id_node_type", "id_node_type", false},
    {"code_node_type", "code_node_type", false},

    {"id_geograph", "id_geograph", false},
    {"fullname_geograph", "fullname_geograph", false},

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
  node->setNumberInGroup(record.value(getFieldAlias("num_node")).toInt());

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
      {":id_geograph", filters.value("geographId")},
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
  saveChildren(node);
}

void PostgresCrud<Node>::upd(const Editor::Shared& node) const {
  Editor<Node>::upd(node);
  this->saveChildren(node);
}

void PostgresCrud<Node>::saveChildren(const Editor::Shared& node) const {
  saveFixtures(node);
  saveGateways(node);
  saveSensors(node);
}

void PostgresCrud<Node>::saveFixtures(const Editor::Shared& node) const {
  auto fixtures = node->getFixtures();
  QSet<ID> currentIds = extractIds(fixtures).toSet();

  QSet<ID> dbIds = selectFixturesIds(node->getId()).toSet();
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteFixtures(idsToDelete.toList());
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertFixtures(node->getId(), idsToInsert.toList());
  }
}

IDList PostgresCrud<Node>::selectFixturesIds(ID nodeId) const {
  const QString sql = "select id_fixture from fixture_pkg_i.fixture_allinfo_vw where id_node = :id_node";
  const BindParamsType params{
      {":id_node", nodeId},
  };
  return selectIds(sql, params);
}

void PostgresCrud<Node>::insertFixtures(ID nodeId, const IDList& ids) const {
  updateFixturesNode(ids, nodeId);
}

void PostgresCrud<Node>::deleteFixtures(const IDList& ids) const {
  updateFixturesNode(ids, 1);
}

void PostgresCrud<Node>::updateFixturesNode(const IDList& fixturesIds, ID nodeId) const {
  const QString sql = "select fixture_pkg_i.set_id_node(:id_fixture, :id_node)";
  updateObjectNode(sql, "id_fixture", fixturesIds, nodeId);
}

void PostgresCrud<Node>::saveGateways(const Shared& node) const {
  auto gateways = node->getGateways();
  QSet<ID> currentIds = extractIds(gateways).toSet();

  QSet<ID> dbIds = selectGatewaysIds(node->getId()).toSet();
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteGateways(idsToDelete.toList());
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertGateways(node->getId(), idsToInsert.toList());
  }
}

IDList PostgresCrud<Node>::selectGatewaysIds(ID nodeId) const {
  const QString sql = "select id_gateway from gateway_pkg_i.gateway_allinfo_vw where id_node = :id_node";
  const BindParamsType params{
      {":id_node", nodeId},
  };
  return selectIds(sql, params);
}

void PostgresCrud<Node>::insertGateways(ID nodeId, const IDList& ids) const {
  updateGatewaysNode(ids, nodeId);
}

void PostgresCrud<Node>::deleteGateways(const IDList& ids) const {
  updateGatewaysNode(ids, 1);
}

void PostgresCrud<Node>::updateGatewaysNode(const IDList& gatewaysIds, ID nodeId) const {
  const QString sql = "select gateway_pkg_i.set_id_node(:id_gateway, :id_node)";
  updateObjectNode(sql, "id_gateway", gatewaysIds, nodeId);
}

void PostgresCrud<Node>::saveSensors(const Shared& node) const {
  auto sensors = node->getSensors();
  QSet<ID> currentIds = extractIds(sensors).toSet();

  QSet<ID> dbIds = selectSensorsIds(node->getId()).toSet();
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteSensors(idsToDelete.toList());
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertSensors(node->getId(), idsToInsert.toList());
  }
}

IDList PostgresCrud<Node>::selectSensorsIds(ID nodeId) const {
  const QString sql = "select id_sensor from sensor_pkg_i.sensor_allinfo_vw where id_node = :id_node";
  const BindParamsType params{
      {":id_node", nodeId},
  };
  return selectIds(sql, params);
}

void PostgresCrud<Node>::insertSensors(ID nodeId, const IDList& ids) const {
  updateSensorsNode(ids, nodeId);
}

void PostgresCrud<Node>::deleteSensors(const IDList& ids) const {
  updateSensorsNode(ids, 1);
}

void PostgresCrud<Node>::updateSensorsNode(const IDList& gatewaysIds, ID nodeId) const {
  const QString sql = "select sensor_pkg_i.set_id_node(:id_sensor, :id_node)";
  updateObjectNode(sql, "id_sensor", gatewaysIds, nodeId);
}

template <typename Container>
IDList PostgresCrud<Node>::extractIds(const Container& container) const {
  IDList ids;
  std::transform(container.begin(),
		 container.end(),
		 std::back_inserter(ids),
		 [](const typename Container::value_type& item) { return item->getId(); });
  return ids;
}

IDList light::PostgresqlGateway::PostgresCrud<Node>::selectIds(const QString& sql, const BindParamsType& params) const {
  SelectQuery selectFixtureIds(getSession()->getDb());
  selectFixtureIds.prepare(sql);
  selectFixtureIds.bind(params);
  selectFixtureIds.exec();
  IDList dbIds;
  for (auto record : selectFixtureIds) {
    auto id = record.value(0).value<ID>();
    dbIds << id;
  }
  return dbIds;
}

void PostgresCrud<Node>::updateObjectNode(const QString& sql,
					  const QString& idFieldName,
					  const IDList& Ids,
					  ID nodeId) const {
  SqlQuery query(getSession()->getDb());
  query.prepare(sql);
  const QString idPlaceholder = ":" + idFieldName;
  for (auto id : Ids) {
    const BindParamsType params{
	{idPlaceholder, id},
	{":id_node", nodeId},
    };
    query.bind(params);
    query.exec();
    query.finish();
  }
}

const QList<Field> nodeContractFields{
    {"id_contract", "id_contract", true},
    {"code_contract", "code_contract", false},
    {"name_contract", "name_contract", false},
};

PostgresCrud<NodeContract>::PostgresCrud() {
  setFields(nodeContractFields);
  setView("node_pkg_i.contract_vw");
}

Reader<NodeContract>::Shared PostgresCrud<NodeContract>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contract> contractCrud;
  auto contract = contractCrud.parse(record);
  auto nodeContract = NodeContractShared::create(*contract);
  return nodeContract;
}

const QList<Field> nodeOwnerFields{
    {"id_owner", "id_owner", true},
    {"code_owner", "code_owner", false},
    {"name_owner", "name_owner", false},
};

PostgresCrud<NodeOwner>::PostgresCrud() {
  setFields(nodeOwnerFields);
  setView("sensor_pkg_i.owner_vw");
}

Reader<NodeOwner>::Shared PostgresCrud<NodeOwner>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setFields({
      {"id_contragent", "id_owner", true},
      {"code", "code_owner", false},
      {"name", "name_owner", false},
  });
  auto contragent = contragentCrud.parse(record);
  auto nodeOwner = NodeOwnerShared::create(*contragent);
  return nodeOwner;
}

} // namespace PostgresqlGateway
} // namespace light
