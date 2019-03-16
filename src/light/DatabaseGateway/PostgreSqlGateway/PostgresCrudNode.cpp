#include "PostgresCrudNode.h"

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudGeograph.h"
#include "PostgresCrudNodeType.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> nodeFields{
    {"id_node", "id_node", true},
    {"n_coordinate", "n_coordinate", false},
    {"e_coordinate", "e_coordinate", false},
    {"price", "price_node", false},
    {"comments", "comments_node", false},

    {"id_node_type", "id_node_type", false},
    {"code_node_type", "code_node_type", false},

    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},
};

PostgresCrud<Node>::PostgresCrud() {
  setFields(nodeFields);
  setView("node_pkg_i.node_vwf(:id_geograph, :id_owner, :id_node_type, :id_contract, :id_gateway)");
  setInsertSql("select node_pkg_i.save(:action, :id_node, :id_contract, :id_equipment_type, "
	       ":id_geograph, :n_coordinate, :e_coordinate, :price, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select node_pkg_i.del(:id)");
}

Editor<Node>::Shared PostgresCrud<Node>::parse(const QSqlRecord& record) const {
  auto node = NodeShared::create();
  node->setId(record.value(getIdAlias()).value<ID>());
  node->setCoordinate(record.value(getFiledAlias("n_coordinate")).toDouble(),
		      record.value(getFiledAlias("e_coordinate")).toDouble());
  node->setPrice(record.value(getFiledAlias("price_node")).toDouble());
  node->setComment(record.value(getFiledAlias("comments_node")).toString());

//  auto ownerId = record.value(5).value<ID>();
  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(getSession());
  node->setOwner(equipmentOwnerCrud.parse(record));

//  auto contractId = record.value(6).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(getSession());
  node->setContract(contractCrud.parse(record));

//  auto geographId = record.value(7).value<ID>();
  PostgresCrud<Geograph> geographCrud;
  geographCrud.setSession(getSession());
  node->setGeograph(geographCrud.parse(record));

//  auto nodeTypeId = record.value(8).value<ID>();
  PostgresCrud<NodeType> nodeTypeCrud;
  nodeTypeCrud.setSession(getSession());
  node->setNodeType(nodeTypeCrud.parse(record));
  return node;
}

BindParamsType PostgresCrud<Node>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_geograph", filters.value("geopraphId")},
      {":id_owner", filters.value("ownerId")},
      {":id_node_type", filters.value("nodeTypeId")},
      {":id_contract", filters.value("contractId")},
      {":id_gateway", filters.value("gatewayId")},
  };
}

BindParamsType PostgresCrud<Node>::getInsertParams(const Editor::Shared& node) const {
  return BindParamsType{
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
}

BindParamsType PostgresCrud<Node>::getUpdateParams(const Editor::Shared& node) const {
  return BindParamsType{
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
}

} // namespace PostgresqlGateway
} // namespace light
