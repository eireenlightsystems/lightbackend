#include "PostgresCrudGateway.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudGatewayType.h"
#include "PostgresCrudNode.h"

#include <QDebug>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> gatewayFields{
    {"id_gateway", "id_gateway", true},
    {"comments", "comments_gateway", false},
    {"name_node_group", "name_node_group_gateway", false},
    {"serial_number", "serial_number_gateway", false},

    {"id_node", "id_node", false},
    {"n_coordinate", "n_coordinate_node", false},
    {"e_coordinate", "e_coordinate_node", false},
    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},

    {"id_gateway_type", "id_gateway_type", false},
    {"code_gateway_type", "code_gateway_type", false},
};

PostgresCrud<Gateway>::PostgresCrud() {
  setFields(gatewayFields);
  setView("gateway_pkg_i.gateway_vwf(:id_geograph, :id_owner, :id_gateway_type, :id_contract, :id_node)");
  setInsertSql("select gateway_pkg_i.save(:action, :id_gateway, :id_contract, :id_equipment_type, "
	       ":id_node, :name_node_group, :serial_number, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select gateway_pkg_i.del(:id)");
}

Editor<Gateway>::Shared PostgresCrud<Gateway>::parse(const QSqlRecord& record) const {
  auto gateway = GatewayShared::create();
  gateway->setId(record.value(getIdAlias()).value<ID>());
  gateway->setComment(record.value(getFieldAlias("comments")).toString());
  gateway->setName(record.value(getFieldAlias("name_node_group")).toString());
  gateway->setSerialNumber(record.value(getFieldAlias("serial_number")).toString());

  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(getSession());
  gateway->setOwner(equipmentOwnerCrud.parse(record));

  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(getSession());
  gateway->setContract(contractCrud.parse(record));

  PostgresCrud<Node> nodeCrud;
  gateway->setNode(nodeCrud.parse(record));

  PostgresCrud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(getSession());
  gateway->setGatewayType(gatewayTypeCrud.parse(record));

  PostgresCrud<Node> childNodesCrud;
  childNodesCrud.setSession(getSession());
  const QVariantHash params{
      {"gatewayId", gateway->getId()},
  };
  gateway->setNodes(childNodesCrud.sel(params));

  return gateway;
}

BindParamsType PostgresCrud<Gateway>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_geograph", filters.value("geopraphId")},
      {":id_owner", filters.value("ownerId")},
      {":id_gateway_type", filters.value("gatewayTypeId")},
      {":id_contract", filters.value("contractId")},
      {":id_node", filters.value("nodeId")},
  };
}

BindParamsType PostgresCrud<Gateway>::getInsertParams(const Shared& gateway) const {
  return BindParamsType{
      {":action", "ins"},
      {":id_gateway", QVariant()},
      {":id_contract", gateway->getContract() ? gateway->getContractId() : QVariant()},
      {":id_equipment_type", gateway->getGatewayType() ? gateway->getGatewayTypeId() : QVariant()},
      {":id_node", gateway->getNode() ? gateway->getNodeId() : QVariant()},
      {":comments", gateway->getComment()},
      {":name_node_group", gateway->getName()},
      {":serial_number", gateway->getSerialNumber()},
  };
}

BindParamsType PostgresCrud<Gateway>::getUpdateParams(const Shared& gateway) const {
  return BindParamsType{
      {":action", "upd"},
      {":id_gateway", gateway->getId()},
      {":id_contract", gateway->getContract() ? gateway->getContractId() : QVariant()},
      {":id_equipment_type", gateway->getGatewayType() ? gateway->getGatewayTypeId() : QVariant()},
      {":id_node", gateway->getNode() ? gateway->getNodeId() : QVariant()},
      {":comments", gateway->getComment()},
      {":name_node_group", gateway->getName()},
      {":serial_number", gateway->getSerialNumber()},
  };
}

void PostgresCrud<Gateway>::ins(const Shared& gateway) const {
  Editor<Gateway>::ins(gateway);

  QSet<ID> idsToInsert;
  for (auto node : gateway->getNodes()) {
    idsToInsert << node->getId();
  }

  insertNewChildNodes(idsToInsert, gateway);
}

void PostgresCrud<Gateway>::upd(const Shared& gateway) const {
  Editor<Gateway>::upd(gateway);
  saveChildNodes(gateway);
}

void PostgresCrud<Gateway>::saveChildNodes(const Shared& gateway) const {
  auto nodes = gateway->getNodes();
  QSet<ID> currentIds;
  for (auto node : nodes) {
    currentIds << node->getId();
  }

  QSet<ID> dbIds = selectCurrentNodesIds(gateway);
  auto idsToDelete = dbIds;
  idsToDelete.subtract(currentIds);

  if (idsToDelete.count()) {
    deleteChildNodes(idsToDelete, gateway);
  }

  auto idsToInsert = currentIds;
  idsToInsert.subtract(dbIds);
  if (idsToInsert.count()) {
    insertNewChildNodes(idsToInsert, gateway);
  }
}

QSet<ID> PostgresCrud<Gateway>::selectCurrentNodesIds(const GatewayShared& gateway) const {
  const QString selectAllFixtureIdSql =
      "select id_node from gateway_pkg_i.node_group_vw where id_gateway = :id_gateway";
  const BindParamsType bindParamsSelectAllId{
      {":id_gateway", gateway->getId()},
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

void PostgresCrud<Gateway>::insertNewChildNodes(const QSet<ID>& idsToInsert, const GatewayShared& gateway) const {
  const QString saveItemSql = "select node_pkg_i.ins_gateway_node(:id_gateway, :id_node, :num_node)";
  InsertQuery insertItemQuery(getSession()->getDb());
  insertItemQuery.prepare(saveItemSql);
  for (auto id : idsToInsert) {
    const BindParamsType bindParamsInsert{
	{":id_gateway", gateway->getId()},
	{":id_node", id},
	{":num_node", 0},
    };
    insertItemQuery.bind(bindParamsInsert);
    insertItemQuery.exec();
    insertItemQuery.finish();
  }
}

void PostgresCrud<Gateway>::deleteChildNodes(const QSet<ID>& idsToDelete, const GatewayShared& gateway) const {
  const QString deleteGroupItemsSql = "select node_pkg_i.del_gateway_node(:id_gateway, :id_node)";
  DeleteQuery deleteGroupItemQuery(getSession()->getDb());
  deleteGroupItemQuery.prepare(deleteGroupItemsSql);
  for (auto id : idsToDelete) {
    const BindParamsType bindParamsDelete{
	{":id_gateway", gateway->getId()},
	{":id_node", id},
    };
    deleteGroupItemQuery.bind(bindParamsDelete);
    deleteGroupItemQuery.exec();
    deleteGroupItemQuery.finish();
  }
}

} // namespace PostgresqlGateway
} // namespace light
