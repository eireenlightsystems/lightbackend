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

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},

    {"id_gateway_type", "id_gateway_type", false},
    {"code_gateway_type", "code_gateway_type", false},

    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},
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

  auto nodeId = record.value(getFieldAlias("id_node")).value<ID>();
  PostgresCrud<Node> nodeCrud;
  nodeCrud.setSession(getSession());
  gateway->setNode(nodeCrud.selById(nodeId));

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
}

void PostgresCrud<Gateway>::upd(const Shared& gateway) const {
  Editor<Gateway>::upd(gateway);
  saveChildNodes(gateway);
}

void PostgresCrud<Gateway>::saveChildNodes(const Shared& gateway) const {
}

void PostgresCrud<Gateway>::insertNewChildNodes(const QSet<ID>& idsToInsert, const GatewayShared& gateway) const {
}

void PostgresCrud<Gateway>::deleteChildNodes(const QSet<ID>& idsToDelete, const GatewayShared& gateway) const {
}

} // namespace PostgresqlGateway
} // namespace light
