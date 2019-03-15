#ifndef GATEWAYCONTROLLER_H
#define GATEWAYCONTROLLER_H

#include "Controller.h"
#include "Gateway.h"

#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Inserter<Gateway, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  IDList ins(const QList<QVariantHash>& params) {
    GatewaySharedList newGateways;

    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<GatewayType> gatewayTypeCrud;
    gatewayTypeCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());

    for (const auto& param : params) {
      auto newGateway = GatewayShared::create();
      if (param.contains("contractId")) {
	ID contractId = param.value("contractId").value<ID>();
	auto contract = contractCrud.selById(contractId);
	newGateway->setContract(contract);
      }

      if (param.contains("gatewayTypeId")) {
	ID gatewayTypeId = param.value("gatewayTypeId").value<ID>();
	auto gatewayType = gatewayTypeCrud.selById(gatewayTypeId);
	newGateway->setGatewayType(gatewayType);
      }

      if (param.contains("nodeId")) {
	ID nodeId = param.value("nodeId").value<ID>();
	auto node = nodeCrud.selById(nodeId);
	newGateway->setNode(node);
      }

      if (param.contains("price")) {
	double price = param.value("price").toDouble();
	newGateway->setPrice(price);
      }

      if (param.contains("comment")) {
	QString comment = param.value("comment").toString();
	newGateway->setComment(comment);
      }

      newGateways << newGateway;
    }

    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(getSession());
    gatewayCrud.save(newGateways);
    IDList result;
    std::transform(newGateways.begin(),
		   newGateways.end(),
		   std::back_inserter(result),
		   [](const GatewayShared& gateway) { return gateway->getId(); });
    return result;
  }
};

template <template <typename> class Crud>
class Updater<Gateway, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<QVariantHash>& params) {
    GatewaySharedList updatedGateways;

    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<GatewayType> gatewayTypeCrud;
    gatewayTypeCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());

    for (const auto& param : params) {
      ID gatewayId = param.value("gatewayId").value<ID>();
      GatewayShared gateway = gatewayCrud.selById(gatewayId);

      if (param.contains("price")) {
	double price = param.value("price").toDouble();
	gateway->setPrice(price);
      }

      if (param.contains("comment")) {
	QString comment = param.value("comment").toString();
	gateway->setComment(comment);
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

  void upd(ID id, const QVariantHash& param) {
    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<GatewayType> gatewayTypeCrud;
    gatewayTypeCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());

    GatewayShared gateway = gatewayCrud.selById(id);

    if (param.contains("price")) {
      double price = param.value("price").toDouble();
      gateway->setPrice(price);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      gateway->setComment(comment);
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
    gatewayCrud.save({gateway});
  }
}; // namespace light

} // namespace light

#endif // GATEWAYCONTROLLER_H
