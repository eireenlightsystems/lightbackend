#ifndef GATEWAYCONTROLLER_H
#define GATEWAYCONTROLLER_H

#include "BadRequestException.h"
#include "Controller.h"
#include "Gateway.h"
#include "NodeController.h"

#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Controller<Gateway, Crud> : public EditableListController<Gateway, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
  void delFromList(ID listId, const IDList& ids) override {
    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(this->getSession());
    GatewayShared gateway = gatewayCrud.selById(listId);
    for (ID id : ids) {
      gateway->removeNode(id);
    }
    gatewayCrud.save({gateway});
  }
  void addToList(ID listId, const IDList& ids) override {
    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(this->getSession());
    GatewayShared gateway = gatewayCrud.selById(listId);

    if (gateway->getNodes().count() + ids.count() > 255) {
      const QString errorText = QString("gateway(id=%1) can not contains more than 255 items").arg(gateway->getId());
      throw BadRequestException(errorText);
    }

    Crud<Node> nodeCrud;
    nodeCrud.setSession(this->getSession());
    auto nodes = nodeCrud.sel(ids);
    gateway->addNodes(nodes);
    gatewayCrud.save({gateway});
  }
};

template <template <typename> class Crud>
IDList Controller<Gateway, Crud>::ins(const QList<QVariantHash>& params) {
  GatewaySharedList newGateways;

  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(this->getSession());
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());

  for (const auto& param : params) {
    auto newGateway = GatewayShared::create();

    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      auto contract = contractCrud.selById(contractId);
      newGateway->setContract(contract);
    } else {
      throw BadRequestException("contractId can not be empty");
    }

    if (param.contains("gatewayTypeId")) {
      ID gatewayTypeId = param.value("gatewayTypeId").value<ID>();
      auto gatewayType = gatewayTypeCrud.selById(gatewayTypeId);
      newGateway->setGatewayType(gatewayType);
    } else {
      throw BadRequestException("gatewayTypeId can not be empty");
    }

    if (param.contains("nodeId")) {
      ID nodeId = param.value("nodeId").value<ID>();
      auto node = nodeCrud.selById(nodeId);
      newGateway->setNode(node);
    } else {
      throw BadRequestException("nodeId can not be empty");
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      newGateway->setSerialNumber(serialNumber);
    }

    if (param.contains("nodeGroupName")) {
      QString nodeGroupName = param.value("nodeGroupName").toString();
      newGateway->setName(nodeGroupName);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      newGateway->setComment(comment);
    }

    newGateways << newGateway;
  }

  Crud<Gateway> gatewayCrud;
  gatewayCrud.setSession(this->getSession());
  gatewayCrud.save(newGateways);
  IDList result;
  std::transform(newGateways.begin(), newGateways.end(), std::back_inserter(result), [](const GatewayShared& gateway) {
    return gateway->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Gateway, Crud>::upd(const QList<QVariantHash>& params) {
  GatewaySharedList updatedGateways;

  Crud<Gateway> gatewayCrud;
  gatewayCrud.setSession(this->getSession());
  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(this->getSession());
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());

  for (const auto& param : params) {
    ID gatewayId = param.value("gatewayId").value<ID>();
    GatewayShared gateway = gatewayCrud.selById(gatewayId);

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      gateway->setComment(comment);
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      gateway->setSerialNumber(serialNumber);
    }

    if (param.contains("nodeGroupName")) {
      QString nodeGroupName = param.value("nodeGroupName").toString();
      gateway->setName(nodeGroupName);
    }

    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      if (gateway->getContractId() != contractId) {
	auto contract = contractCrud.selById(contractId);
	gateway->setContract(contract);
      }
    }

    if (param.contains("gatewayTypeId")) {
      ID gatewayTypeId = param.value("gatewayTypeId").value<ID>();
      if (gateway->getGatewayTypeId() != gatewayTypeId) {
	auto gatewayType = gatewayTypeCrud.selById(gatewayTypeId);
	gateway->setGatewayType(gatewayType);
      }
    }

    if (param.contains("nodeId")) {
      ID nodeId = param.value("nodeId").value<ID>();
      if (gateway->getNodeId() != nodeId) {
	auto node = nodeCrud.selById(nodeId);
	gateway->setNode(node);
      }
    }
    updatedGateways << gateway;
  }

  gatewayCrud.save(updatedGateways);
}

template <template <typename> class Crud>
void Controller<Gateway, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["gatewayId"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // GATEWAYCONTROLLER_H
