#include "PostgresCrudGateway.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudGatewayType.h"
#include "PostgresCrudNode.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<Gateway>::PostgresCrud() {
  setIdField("id_gateway");
  setFields(QStringList() << getIdField() << "price"
			  << "comments"
			  << "id_owner"
			  << "id_contract"
			  << "id_node"
			  << "id_gateway_type");
  setView("gateway_pkg_i.gateway_vwf(:id_geograph, :id_owner, :id_gateway_type, :id_contract, :id_node)");
  setInsertSql("select gateway_pkg_i.save(:action, :id_gateway, :id_contract, :id_equipment_type, "
	       ":id_node, :price, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select gateway_pkg_i.del(:id)");
}

Editor<Gateway>::Shared PostgresCrud<Gateway>::parse(const QSqlRecord& record) const {
  auto gateway = GatewayShared::create();
  gateway->setId(record.value(0).value<ID>());
  gateway->setPrice(record.value(1).toDouble());
  gateway->setComment(record.value(2).toString());

  auto ownerId = record.value(3).value<ID>();
  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(getSession());
  gateway->setOwner(equipmentOwnerCrud.selById(ownerId));

  auto contractId = record.value(4).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(getSession());
  gateway->setContract(contractCrud.selById(contractId));

  auto geographId = record.value(5).value<ID>();
  PostgresCrud<Node> nodeCrud;
  nodeCrud.setSession(getSession());
  gateway->setNode(nodeCrud.selById(geographId));

  auto gatewayTypeId = record.value(6).value<ID>();
  PostgresCrud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(getSession());
  gateway->setGatewayType(gatewayTypeCrud.selById(gatewayTypeId));

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

BindParamsType PostgresCrud<Gateway>::getInsertParams(const Editor::Shared& gateway) const {
  return BindParamsType{
      {":action", "ins"},
      {":id_gateway", QVariant()},
      {":id_contract", gateway->getContract() ? gateway->getContractId() : QVariant()},
      {":id_equipment_type", gateway->getGatewayType() ? gateway->getGatewayTypeId() : QVariant()},
      {":id_node", gateway->getNode() ? gateway->getNodeId() : QVariant()},
      {":price", gateway->getPrice()},
      {":comments", gateway->getComment()},
  };
}

BindParamsType PostgresCrud<Gateway>::getUpdateParams(const Editor::Shared& gateway) const {
  return BindParamsType{
      {":action", "upd"},
      {":id_gateway", gateway->getId()},
      {":id_contract", gateway->getContract() ? gateway->getContractId() : QVariant()},
      {":id_equipment_type", gateway->getGatewayType() ? gateway->getGatewayTypeId() : QVariant()},
      {":id_node", gateway->getNode() ? gateway->getNodeId() : QVariant()},
      {":price", gateway->getPrice()},
      {":comments", gateway->getComment()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
