#include "PostgresNodeGateway.h"

#include "Node.h"

namespace light {
namespace PostgresqlGateway {

NodeShared PostgresNodeGateway::selectNode(ID id) {
  auto nodes = selectNodes({id});
  if (nodes.count()) {
    return nodes.first();
  }

  return NodeShared();
}

NodeSharedList PostgresNodeGateway::selectNodes(const QList<ID>& ids) {
  NodeSharedList result;
  const QString sql =
      "select id_node, e_coordinate, n_coordinate, price, comments "
      "from node_pkg_i.node_vwf "
      "where id_node = :id_node";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_node", id},
    };
    result << selectBase(sql, bindParams);
  }
  return result;
}

void PostgresNodeGateway::saveNode(const NodeShared& node) {
}

void PostgresNodeGateway::saveNodes(const NodeSharedList& nodes) {
}

void PostgresNodeGateway::deleteNode(const NodeShared& node) {
}

void PostgresNodeGateway::deleteNodes(const NodeSharedList& nodes) {
}

NodeSharedList PostgresNodeGateway::selectBase(const QString &sql, const BindParamsType &params) const
{
  auto parser = std::bind(&PostgresNodeGateway::parseNode, this, std::placeholders::_1);
  return select<NodeSharedList>(sql, params, parser);
}

NodeShared PostgresNodeGateway::parseNode(const QSqlRecord &record) const
{
  auto node = NodeShared::create();
  node->setId(record.value(0).value<ID>());
  node->setCoordinate(record.value(1).toDouble(), record.value(2).toDouble());
  node->setPrice(record.value(3).toDouble());
  node->setComment(record.value(4).toString());

//  node->setOwner();
//  node->setContract();
//  node->setGeograph();
//  node->setEquipmentType();
  return node;
}

} // namespace PostgresqlGateway
} // namespace light
