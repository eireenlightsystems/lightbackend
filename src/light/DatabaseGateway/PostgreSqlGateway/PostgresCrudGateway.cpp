#include "PostgresCrudGateway.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
GatewaySharedList PostgresCrud<Gateway>::sel(const IDList& ids) const {
  GatewaySharedList result;
  const QString sql =
      "select id_gateway, price, comments, id_owner, id_contract, id_node, id_gateway_type "
      "from gateway_pkg_i.gateway_vwf(:id_geograph, :id_owner, :id_gateway_type, :id_contract, :id_node) "
      "where id_gateway = :id_gateway";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_geograph", QVariant()},
	{":id_owner", QVariant()},
	{":id_gateway_type", QVariant()},
	{":id_contract", QVariant()},
	{":id_node", QVariant()},
	{":id_gateway", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
template <>
GatewaySharedList PostgresCrud<Gateway>::sel<ID, ID, ID, ID, ID>(ID geopraphId,
								 ID ownerId,
								 ID gatewayTypeId,
								 ID contractId,
								 ID nodeId) const {
  GatewaySharedList result;
  const QString sql =
      "select id_gateway, price, comments, id_owner, id_contract, id_node, id_gateway_type "
      "from gateway_pkg_i.gateway_vwf(:id_geograph, :id_owner, :id_gateway_type, :id_contract, :id_node) ";
  const BindParamsType bindParams{
      {":id_geograph", geopraphId ? geopraphId : QVariant()},
      {":id_owner", ownerId ? ownerId : QVariant()},
      {":id_gateway_type", gatewayTypeId ? gatewayTypeId : QVariant()},
      {":id_contract", contractId ? contractId : QVariant()},
      {":id_node", nodeId ? nodeId : QVariant()},
  };
  result = selBase(sql, bindParams);
  return result;
}

template <>
template <>
GatewaySharedList PostgresCrud<Gateway>::sel<QVariantHash>(const QVariantHash filters) const {
  GatewaySharedList result;
  const QString sql =
      "select id_gateway, price, comments, id_owner, id_contract, id_node, id_gateway_type "
      "from gateway_pkg_i.gateway_vwf(:id_geograph, :id_owner, :id_gateway_type, :id_contract, :id_node) ";
  const BindParamsType bindParams{
      {":id_geograph", filters.value("geopraphId")},
      {":id_owner", filters.value("ownerId")},
      {":id_gateway_type", filters.value("gatewayTypeId")},
      {":id_contract", filters.value("contractId")},
      {":id_node", filters.value("nodeId")},
  };
  result = selBase(sql, bindParams);
  return result;
}

template <>
void PostgresCrud<Gateway>::ins(const GatewayShared& gateway) const {
  const QString saveSql = "select gateway_pkg_i.save(:action, :id_gateway, :id_contract, :id_equipment_type, "
			  ":id_node, :price, :comments)";
  BindParamsType bindParams{
      {":action", "ins"},
      {":id_gateway", QVariant()},
      {":id_contract", gateway->getContract() ? gateway->getContractId() : QVariant()},
      {":id_equipment_type", gateway->getGatewayType() ? gateway->getGatewayTypeId() : QVariant()},
      {":id_node", gateway->getNode() ? gateway->getNodeId() : QVariant()},
      {":price", gateway->getPrice()},
      {":comments", gateway->getComment()},
  };
  auto query = buildAndExecQuery<InsertQuery>(saveSql, bindParams, session);
}

template <>
void PostgresCrud<Gateway>::upd(const GatewayShared& gateway) const {
  const QString saveSql = "select gateway_pkg_i.save(:action, :id_gateway, :id_contract, :id_equipment_type, "
			  ":id_node, :price, :comments)";
  BindParamsType bindParams{
      {":action", "upd"},
      {":id_gateway", gateway->getId()},
      {":id_contract", gateway->getContract() ? gateway->getContractId() : QVariant()},
      {":id_equipment_type", gateway->getGatewayType() ? gateway->getGatewayTypeId() : QVariant()},
      {":id_node", gateway->getNode() ? gateway->getNodeId() : QVariant()},
      {":price", gateway->getPrice()},
      {":comments", gateway->getComment()},
  };
  auto query = buildAndExecQuery<InsertQuery>(saveSql, bindParams, session);
}

template <>
void PostgresCrud<Gateway>::del(const GatewaySharedList& gateways) const {
  const QString deleteSql = "select gateway_pkg_i.del(:id)";
  QVariantList bindIds;
  std::transform(gateways.begin(), gateways.end(), std::back_inserter(bindIds), [](const GatewayShared& gateway) {
    return QVariant(gateway->getId());
  });
  BindParamsType bindParams{
      {":id", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteSql, bindParams, session);
}

template <>
GatewayShared PostgresCrud<Gateway>::parse(const QSqlRecord& record) const {
  auto gateway = GatewayShared::create();
  gateway->setId(record.value(0).value<ID>());
  gateway->setPrice(record.value(1).toDouble());
  gateway->setComment(record.value(2).toString());

  auto ownerId = record.value(3).value<ID>();
  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(session);
  gateway->setOwner(equipmentOwnerCrud.selById(ownerId));

  auto contractId = record.value(4).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(session);
  gateway->setContract(contractCrud.selById(contractId));

  auto geographId = record.value(5).value<ID>();
  PostgresCrud<Node> nodeCrud;
  nodeCrud.setSession(session);
  gateway->setNode(nodeCrud.selById(geographId));

  auto gatewayTypeId = record.value(6).value<ID>();
  PostgresCrud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(session);
  gateway->setGatewayType(gatewayTypeCrud.selById(gatewayTypeId));

  return gateway;
}

} // namespace PostgresqlGateway
} // namespace light
