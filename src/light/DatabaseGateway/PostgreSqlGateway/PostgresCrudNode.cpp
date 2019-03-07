#include "PostgresCrudNode.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
NodeSharedList PostgresCrud<Node>::sel(const IDList& ids) const {
  NodeSharedList result;
  const QString sql =
      "select id_node, e_coordinate, n_coordinate, price, comments, id_owner, id_contract, id_geograph, id_node_type "
      "from node_pkg_i.node_vwf(:id_geograph, :id_owner, :id_node_type, :id_contract, :id_gateway) "
      "where id_node = :id_node";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_geograph", QVariant()},
	{":id_owner", QVariant()},
	{":id_node_type", QVariant()},
	{":id_contract", QVariant()},
	{":id_gateway", QVariant()},
	{":id_node", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
template <>
NodeSharedList PostgresCrud<Node>::sel<ID, ID, ID, ID, ID>(ID geopraphId,
							   ID ownerId,
							   ID nodeTypeId,
							   ID contractId,
							   ID gatewayId) const {
  NodeSharedList result;
  const QString sql =
      "select id_node, n_coordinate, e_coordinate, price, comments, id_owner, id_contract, id_geograph, id_node_type "
      "from node_pkg_i.node_vwf(:id_geograph, :id_owner, :id_node_type, :id_contract, :id_gateway) ";
  const BindParamsType bindParams{
      {":id_geograph", geopraphId ? geopraphId : QVariant()},
      {":id_owner", ownerId ? ownerId : QVariant()},
      {":id_node_type", nodeTypeId ? nodeTypeId : QVariant()},
      {":id_contract", contractId ? contractId : QVariant()},
      {":id_gateway", gatewayId ? gatewayId : QVariant()},
  };
  result = selBase(sql, bindParams);
  return result;
}

template <>
void PostgresCrud<Node>::ins(const NodeShared& node) const {
  const QString insertSql = "select node_pkg_i.save(:action, :id_node, :id_contract, :id_equipment_type, "
			    ":id_geograph, :n_coordinate, :e_coordinate, :price, :comments)";
  BindParamsType bindParams{
      {":action", "ins"},
      {":id_node", QVariant()},
      {":id_contract", node->getContract() ? node->getContractId() : QVariant()},
      {":id_equipment_type", node->getNodeType() ? node->getNodeTypeId() : QVariant()},
      {":id_geograph", node->getGeograph() ? node->getGeographId() : QVariant()},
      {":n_coordinate", node->getLatitude()},
      {":e_coordinate", node->getLongitude()},
      {":price", node->getPrice()},
      {":comments", node->getComment()},
  };
  auto query = buildAndExecQuery<InsertQuery>(insertSql, bindParams, session);
}

template <>
void PostgresCrud<Node>::upd(const NodeShared& node) const {
  const QString sql = "select node_pkg_i.save(:action, :id_node, :id_contract, :id_equipment_type, "
		      ":id_geograph, :n_coordinate, :e_coordinate, :price, :comments)";
  BindParamsType bindParams{
      {":action", "upd"},
      {":id_node", node->getId()},
      {":id_contract", node->getContract() ? node->getContractId() : QVariant()},
      {":id_equipment_type", node->getNodeType() ? node->getNodeTypeId() : QVariant()},
      {":id_geograph", node->getGeograph() ? node->getGeographId() : QVariant()},
      {":n_coordinate", node->getLatitude()},
      {":e_coordinate", node->getLongitude()},
      {":price", node->getPrice()},
      {":comments", node->getComment()},
  };
  buildAndExecQuery<UpdateQuery>(sql, bindParams, session);
}

template <>
void PostgresCrud<Node>::del(const NodeSharedList& nodes) const {
  const QString deleteSql = "select node_pkg_i.del(:id_node)";
  QVariantList bindIds;
  std::transform(nodes.begin(), nodes.end(), std::back_inserter(bindIds), [](const NodeShared& node) {
    return QVariant(node->getId());
  });
  BindParamsType bindParams{
      {":id_node", bindIds},
  };
  buildAndExecBatchQuery<DeleteQuery>(deleteSql, bindParams, session);
}

template <>
NodeShared PostgresCrud<Node>::parse(const QSqlRecord& record) const {
  auto node = NodeShared::create();
  node->setId(record.value(0).value<ID>());
  node->setCoordinate(record.value(1).toDouble(), record.value(2).toDouble());
  node->setPrice(record.value(3).toDouble());
  node->setComment(record.value(4).toString());

  auto ownerId = record.value(5).value<ID>();
  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(session);
  node->setOwner(equipmentOwnerCrud.selById(ownerId));

  auto contractId = record.value(6).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(session);
  node->setContract(contractCrud.selById(contractId));

  auto geographId = record.value(7).value<ID>();
  PostgresCrud<Geograph> geographCrud;
  geographCrud.setSession(session);
  node->setGeograph(geographCrud.selById(geographId));

  auto nodeTypeId = record.value(8).value<ID>();
  PostgresCrud<NodeType> nodeTypeCrud;
  nodeTypeCrud.setSession(session);
  node->setNodeType(nodeTypeCrud.selById(nodeTypeId));
  return node;
}

} // namespace PostgresqlGateway
} // namespace light
