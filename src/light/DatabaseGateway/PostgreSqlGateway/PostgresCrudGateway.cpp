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

const QList<Field> gatewayFields {
    {"id_gateway", "id_gateway", true},
    {"price", "price_gateway", false},
    {"comments", "comments_gateway", false},

    {"id_node", "id_node", false},

    {"id_owner", "id_contragent", false},
    {"id_owner", "code_contragent", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},

    {"id_gateway_type", "id_gateway_type", false},
    {"code_gateway_type", "code_gateway_type", false},
};

PostgresCrud<Gateway>::PostgresCrud() {
  setFields(gatewayFields);
  setView("gateway_pkg_i.gateway_vwf(:id_geograph, :id_owner, :id_gateway_type, :id_contract, :id_node)");
  setInsertSql("select gateway_pkg_i.save(:action, :id_gateway, :id_contract, :id_equipment_type, "
	       ":id_node, :price, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select gateway_pkg_i.del(:id)");
}

Editor<Gateway>::Shared PostgresCrud<Gateway>::parse(const QSqlRecord& record) const {
  auto gateway = GatewayShared::create();
  gateway->setId(record.value(getIdAlias()).value<ID>());
  gateway->setPrice(record.value(getFiledAlias("price_gateway")).toDouble());
  gateway->setComment(record.value(getFiledAlias("comments_gateway")).toString());

  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(getSession());
  gateway->setOwner(equipmentOwnerCrud.parse(record));

  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(getSession());
  gateway->setContract(contractCrud.parse(record));

  auto nodeId = record.value(getFiledAlias("id_node")).value<ID>();
  PostgresCrud<Node> nodeCrud;
  nodeCrud.setSession(getSession());
  gateway->setNode(nodeCrud.selById(nodeId));

  PostgresCrud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(getSession());
  gateway->setGatewayType(gatewayTypeCrud.parse(record));

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
