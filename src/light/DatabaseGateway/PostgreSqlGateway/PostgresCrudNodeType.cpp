#include "PostgresCrudNodeType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
template <>
NodeTypeSharedList PostgresCrud<NodeType>::sel<>() const {
  NodeTypeSharedList result;
  const QString sql = "select id_node_type, code_node_type "
		      "from node_pkg_i.node_type_vw";
  const BindParamsType bindParams{};
  result << selBase(sql, bindParams);
  return result;
}

template <>
NodeTypeSharedList PostgresCrud<NodeType>::sel(const IDList& ids) const {
  NodeTypeSharedList result;
  const QString sql = "select id_node_type, code_node_type "
		      "from node_pkg_i.node_type_vw "
		      "where id_node_type = :id_node_type";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_node_type", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
NodeTypeShared PostgresCrud<NodeType>::parse(const QSqlRecord& record) const {
  auto nodeType = NodeTypeShared::create();
  nodeType->setId(record.value(0).value<ID>());
  nodeType->setCode(record.value(1).toString());
  return nodeType;
}

} // namespace PostgresqlGateway
} // namespace light
