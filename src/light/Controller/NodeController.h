#ifndef NODECONTROLLER_H
#define NODECONTROLLER_H

#include "Controller.h"
#include "Node.h"
#include "Fixture.h"
#include "Gateway.h"
#include "Sensor.h"


#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Controller<Node, Crud> : public EditableController<Node, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
  void addFixtures(ID nodeId, const IDList& fixturesIds);
  void delFixtures(ID nodeId, const IDList& fixturesIds);
  void addGateways(ID nodeId, const IDList& gatewaysIds);
  void delGateways(ID nodeId, const IDList& gatewaysIds);
  void addSensors(ID nodeId, const IDList& sensorsIds);
  void delSensors(ID nodeId, const IDList& sensorsIds);
};

template <template <typename> class Crud>
IDList Controller<Node, Crud>::ins(const QList<QVariantHash>& params) {
  NodeSharedList newNodes;

  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<NodeType> nodeTypeCrud;
  nodeTypeCrud.setSession(this->getSession());
  Crud<Geograph> geographCrud;
  geographCrud.setSession(this->getSession());

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

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      newNode->setComment(comment);
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      newNode->setSerialNumber(serialNumber);
    }

    newNodes << newNode;
  }

  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  nodeCrud.save(newNodes);
  IDList result;
  std::transform(newNodes.begin(), newNodes.end(), std::back_inserter(result), [](const NodeShared& node) {
    return node->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Node, Crud>::upd(const QList<QVariantHash>& params) {
  NodeSharedList nodes;

  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<NodeType> nodeTypeCrud;
  nodeTypeCrud.setSession(this->getSession());
  Crud<Geograph> geographCrud;
  geographCrud.setSession(this->getSession());

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

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      node->setComment(comment);
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      node->setSerialNumber(serialNumber);
    }

    nodes << node;
  }

  nodeCrud.save(nodes);
}

template <template <typename> class Crud>
void Controller<Node, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["nodeId"] = id;
  return upd({fullParam});
}

template <template <typename> class Crud>
void Controller<Node, Crud>::addFixtures(ID nodeId, const IDList& fixturesIds) {
  Crud<Fixture> fixtureCrud;
  fixtureCrud.setSession(this->getSession());
  auto fixtures = fixtureCrud.sel(fixturesIds);

  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  auto node = nodeCrud.selById(nodeId);
  node->addFixtures(fixtures);

  nodeCrud.save(node);
}

template <template <typename> class Crud>
void Controller<Node, Crud>::delFixtures(ID nodeId, const IDList& fixturesIds) {
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  auto node = nodeCrud.selById(nodeId);
  node->removeFixtures(fixturesIds);

  nodeCrud.save(node);
}

template <template <typename> class Crud>
void Controller<Node, Crud>::addGateways(ID nodeId, const IDList& gatewaysIds) {
  Crud<Gateway> gatewayCrud;
  gatewayCrud.setSession(this->getSession());
  auto gateways = gatewayCrud.sel(gatewaysIds);

  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  auto node = nodeCrud.selById(nodeId);
  node->addGateways(gateways);

  nodeCrud.save(node);
}

template <template <typename> class Crud>
void Controller<Node, Crud>::delGateways(ID nodeId, const IDList& gatewaysIds) {
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  auto node = nodeCrud.selById(nodeId);
  node->removeGateways(gatewaysIds);

  nodeCrud.save(node);
}

template <template <typename> class Crud>
void Controller<Node, Crud>::addSensors(ID nodeId, const IDList& sensorsIds) {
  Crud<Sensor> sensorCrud;
  sensorCrud.setSession(this->getSession());
  auto sensors = sensorCrud.sel(sensorsIds);

  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  auto node = nodeCrud.selById(nodeId);
  node->addSensors(sensors);

  nodeCrud.save(node);
}

template <template <typename> class Crud>
void Controller<Node, Crud>::delSensors(ID nodeId, const IDList& sensorsIds) {
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());
  auto node = nodeCrud.selById(nodeId);
  node->removeSensors(sensorsIds);

  nodeCrud.save(node);
}

} // namespace light

#endif // NODECONTROLLER_H
