#include "PostgresCrudNodeType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<NodeType>::PostgresCrud() {
  setIdField("id_node_type");
  setFields(QStringList() << getIdField() << "code_node_type");
  setView("node_pkg_i.node_type_vw");
}

Reader<NodeType>::Shared PostgresCrud<NodeType>::parse(const QSqlRecord& record) const {
  auto nodeType = NodeTypeShared::create();
  nodeType->setId(record.value(0).value<ID>());
  nodeType->setCode(record.value(1).toString());
  return nodeType;
}

} // namespace PostgresqlGateway
} // namespace light
