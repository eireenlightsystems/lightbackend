#include "PostgresCrudNodeType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> nodeTypeFields{
    {"id_node_type", "id_node_type", true},
    {"code_node_type", "code_node_type", false},
};

PostgresCrud<NodeType>::PostgresCrud() {
  setFields(nodeTypeFields);
  setView("node_pkg_i.node_type_vw");
}

Reader<NodeType>::Shared PostgresCrud<NodeType>::parse(const QSqlRecord& record) const {
  auto nodeType = NodeTypeShared::create();
  nodeType->setId(record.value(getIdAlias()).value<ID>());
  nodeType->setCode(record.value(getFiledAlias("code_node_type")).toString());
  return nodeType;
}

} // namespace PostgresqlGateway
} // namespace light
