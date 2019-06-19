#include "PostgresCrudNodeType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> nodeTypeFields{
    {"id_equipment_type", "id_node_type", true},
    {"code", "code_node_type", false},
    {"name", "name_node_type", false},
    {"model", "model_node_type", false},
    {"comments", "comments_node_type", false},
    {"height", "height_node_type", false},
};

PostgresCrud<NodeType>::PostgresCrud() {
  setFields(nodeTypeFields);
  setView("node_type_pkg_i.node_type_vwf()");
  setInsertSql("select node_type_pkg_i.save(:action, :id_equipment_type, :code, :name, :model, :comments, :height)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select node_type_pkg_i.del(:id)");
}

Reader<NodeType>::Shared PostgresCrud<NodeType>::parse(const QSqlRecord& record) const {
  auto nodeType = NodeTypeShared::create();
  nodeType->setId(record.value(getIdAlias()).value<ID>());
  nodeType->setCode(record.value(getFieldAlias("code")).toString());
  nodeType->setName(record.value(getFieldAlias("name")).toString());
  nodeType->setModel(record.value(getFieldAlias("model")).toString());
  nodeType->setComment(record.value(getFieldAlias("comments")).toString());
  nodeType->setHeight(record.value(getFieldAlias("height")).toDouble());
  return nodeType;
}


BindParamsType PostgresCrud<NodeType>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<NodeType>::getInsertParams(const Editor::Shared &nodeType) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_equipment_type", QVariant()},
      {":code", nodeType->getCode()},
      {":name", nodeType->getName()},
      {":model", nodeType->getModel()},
      {":comments", nodeType->getComment()},
      {":height", nodeType->getHeight()},
  };
}

BindParamsType PostgresCrud<NodeType>::getUpdateParams(const Editor::Shared &nodeType) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_equipment_type", nodeType->getId()},
      {":code", nodeType->getCode()},
      {":name", nodeType->getName()},
      {":model", nodeType->getModel()},
      {":comments", nodeType->getComment()},
      {":height", nodeType->getHeight()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
