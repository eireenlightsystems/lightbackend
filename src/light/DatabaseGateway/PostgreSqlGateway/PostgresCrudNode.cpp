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

PostgresCrud<Node>::PostgresCrud() {
  setIdField("id_node");
  setFields(QStringList() << getIdField() << "n_coordinate"
			  << "e_coordinate"
			  << "price"
			  << "comments"
			  << "id_owner"
			  << "id_contract"
			  << "id_geograph"
			  << "id_node_type");
  setView("node_pkg_i.node_vwf(:id_geograph, :id_owner, :id_node_type, :id_contract, :id_gateway)");
  setInsertSql("select node_pkg_i.save(:action, :id_node, :id_contract, :id_equipment_type, "
	       ":id_geograph, :n_coordinate, :e_coordinate, :price, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select node_pkg_i.del(:id)");
}

Editor<Node>::Shared PostgresCrud<Node>::parse(const QSqlRecord& record) const {
  auto node = NodeShared::create();
  node->setId(record.value(0).value<ID>());
  node->setCoordinate(record.value(1).toDouble(), record.value(2).toDouble());
  node->setPrice(record.value(3).toDouble());
  node->setComment(record.value(4).toString());

  auto ownerId = record.value(5).value<ID>();
  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  equipmentOwnerCrud.setSession(getSession());
  node->setOwner(equipmentOwnerCrud.selById(ownerId));

  auto contractId = record.value(6).value<ID>();
  PostgresCrud<Contract> contractCrud;
  contractCrud.setSession(getSession());
  node->setContract(contractCrud.selById(contractId));

  auto geographId = record.value(7).value<ID>();
  PostgresCrud<Geograph> geographCrud;
  geographCrud.setSession(getSession());
  node->setGeograph(geographCrud.selById(geographId));

  auto nodeTypeId = record.value(8).value<ID>();
  PostgresCrud<NodeType> nodeTypeCrud;
  nodeTypeCrud.setSession(getSession());
  node->setNodeType(nodeTypeCrud.selById(nodeTypeId));
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
