#ifndef NODECONTROLLER_H
#define NODECONTROLLER_H

#include "Controller.h"
#include "Node.h"

#include <QVariant>

namespace light {

struct NodeInsertParameters
{
  ID contractId;
  ID nodeTypeId;
  ID geographId;
  QGeoCoordinate coordinate;
  double price;
  QString comment;
};

struct NodeUpdateParameters : public NodeInsertParameters
{
  ID nodeId;
};

template <template <typename> class Crud>
class Inserter<Node, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  IDList ins(const QList<QVariantHash>& params) {
    NodeSharedList newNodes;

    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<NodeType> nodeTypeCrud;
    nodeTypeCrud.setSession(getSession());
    Crud<Geograph> geographCrud;
    geographCrud.setSession(getSession());

    for (const auto& param : params) {
      auto newNode = NodeShared::create();
      if (param.contains("contractId")) {
	ID contractId = param.value("contractId").value<ID>();
	auto contract = contractCrud.selById(contractId);
	newNode->setContract(contract);
      }

      if (param.contains("nodeTypeId")) {
	ID nodeTypeId = param.value("nodeTypeId").value<ID>();
	auto nodeType = nodeTypeCrud.selById(nodeTypeId);
	newNode->setNodeType(nodeType);
      }

      if (param.contains("geographId")) {
	ID geographId = param.value("geographId").value<ID>();
	auto geograph = geographCrud.selById(geographId);
	newNode->setGeograph(geograph);
      }

      if (param.contains("n_coordinate") and param.contains("e_coordinate")) {
	double latitude = param.value("n_coordinate").toDouble();
	double longitude = param.value("e_coordinate").toDouble();
	newNode->setCoordinate(latitude, longitude);
      }

      if (param.contains("price")) {
	double price = param.value("price").toDouble();
	newNode->setPrice(price);
      }

      if (param.contains("comment")) {
	QString comment = param.value("comment").toString();
	newNode->setComment(comment);
      }

      newNodes << newNode;
    }

    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    nodeCrud.save(newNodes);
    IDList result;
    std::transform(newNodes.begin(), newNodes.end(), std::back_inserter(result), [](const NodeShared& node) {
      return node->getId();
    });
    return result;
  }
};

struct NodeCoordinateParameters
{
  ID nodeId;
  QGeoCoordinate coordinate;
};

template <template <typename> class Crud>
class Updater<Node, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<QVariantHash>& params) {
    NodeSharedList nodes;

    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<NodeType> nodeTypeCrud;
    nodeTypeCrud.setSession(getSession());
    Crud<Geograph> geographCrud;
    geographCrud.setSession(getSession());

    for (const auto& param : params) {
      ID nodeId = param.value("nodeId").value<ID>();
      NodeShared node = nodeCrud.selById(nodeId);
      if (param.contains("contractId")) {
	ID contractId = param.value("contractId").value<ID>();
	auto contract = contractCrud.selById(contractId);
	node->setContract(contract);
      }

      if (param.contains("nodeTypeId")) {
	ID nodeTypeId = param.value("nodeTypeId").value<ID>();
	auto nodeType = nodeTypeCrud.selById(nodeTypeId);
	node->setNodeType(nodeType);
      }

      if (param.contains("geographId")) {
	ID geographId = param.value("geographId").value<ID>();
	auto geograph = geographCrud.selById(geographId);
	node->setGeograph(geograph);
      }

      if (param.contains("n_coordinate") and param.contains("e_coordinate")) {
	double latitude = param.value("n_coordinate").toDouble();
	double longitude = param.value("e_coordinate").toDouble();
	node->setCoordinate(latitude, longitude);
      }

      if (param.contains("price")) {
	double price = param.value("price").toDouble();
	node->setPrice(price);
      }

      if (param.contains("comment")) {
	QString comment = param.value("comment").toString();
	node->setComment(comment);
      }

      nodes << node;
    }

    nodeCrud.save(nodes);
  }

  void upd(ID id, const QVariantHash& param) {
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<NodeType> nodeTypeCrud;
    nodeTypeCrud.setSession(getSession());
    Crud<Geograph> geographCrud;
    geographCrud.setSession(getSession());

    NodeShared node = nodeCrud.selById(id);
    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      auto contract = contractCrud.selById(contractId);
      node->setContract(contract);
    }

    if (param.contains("nodeTypeId")) {
      ID nodeTypeId = param.value("nodeTypeId").value<ID>();
      auto nodeType = nodeTypeCrud.selById(nodeTypeId);
      node->setNodeType(nodeType);
    }

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      auto geograph = geographCrud.selById(geographId);
      node->setGeograph(geograph);
    }

    if (param.contains("n_coordinate") and param.contains("e_coordinate")) {
      double latitude = param.value("n_coordinate").toDouble();
      double longitude = param.value("e_coordinate").toDouble();
      node->setCoordinate(latitude, longitude);
    }

    if (param.contains("price")) {
      double price = param.value("price").toDouble();
      node->setPrice(price);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      node->setComment(comment);
    }
    nodeCrud.save({node});
  }
};

} // namespace light

#endif // NODECONTROLLER_H
