#ifndef NODECONTROLLER_H
#define NODECONTROLLER_H

#include "Controller.h"
#include "JsonToNodeConverter.h"
#include "Node.h"

#include <QDebug>

namespace light {

template <template <typename> class Crud>
class Inserter<Node, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void ins(const QList<NodeSaveParameters> params) {
    NodeSharedList newNodes;

    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<NodeType> nodeTypeCrud;
    nodeTypeCrud.setSession(getSession());
    Crud<Geograph> geographCrud;
    geographCrud.setSession(getSession());

    for (const auto& param : params) {
      auto contract = contractCrud.selById(param.contractId);
      auto nodeType = nodeTypeCrud.selById(param.nodeTypeId);
      auto geograph = geographCrud.selById(param.geographId);

      auto newNode = NodeShared::create();
      newNode->setCoordinate(param.coordinate);
      newNode->setPrice(param.price);
      newNode->setComment(param.comment);

      newNode->setGeograph(geograph);
      newNode->setContract(contract);
      newNode->setNodeType(nodeType);

      newNodes << newNode;
    }

    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());
    nodeCrud.save(newNodes);
  }
};

template <template <typename> class Crud>
class Updater<Node, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<NodeSaveParameters> params) {
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
      NodeShared node = nodeCrud.selById(param.nodeId);
      node->setCoordinate(param.coordinate);
      node->setPrice(param.price);
      node->setComment(param.comment);

      if (node->getContractId() != param.contractId) {
	auto contract = contractCrud.selById(param.contractId);
	node->setContract(contract);
      }

      if (node->getNodeTypeId() != param.nodeTypeId) {
	auto nodeType = nodeTypeCrud.selById(param.nodeTypeId);
	node->setNodeType(nodeType);
      }

      if (node->getGeographId() != param.geographId) {
	auto geograph = geographCrud.selById(param.geographId);
	node->setGeograph(geograph);
      }
      nodes << node;
    }

    nodeCrud.save(nodes);
  }

  template <typename... Args>
  void upd(const QList<NodeCoordinateParameters> params) {
    NodeSharedList nodes;

    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());

    for (const auto& param : params) {
      NodeShared node = nodeCrud.selById(param.nodeId);
      node->setCoordinate(param.coordinate);
      nodes << node;
    }

    nodeCrud.save(nodes);
  }
};

} // namespace light

#endif // NODECONTROLLER_H
