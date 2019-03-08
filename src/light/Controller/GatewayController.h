#ifndef GATEWAYCONTROLLER_H
#define GATEWAYCONTROLLER_H

#include "Controller.h"
#include "Gateway.h"

namespace light {

struct GatewayInsertParameters
{
  ID contractId;
  ID gatewayTypeId;
  ID nodeId;
  double price;
  QString comment;
};

struct GatewayUpdateParameters : public GatewayInsertParameters
{
  ID gatewayId;
};

template <template <typename> class Crud>
class Inserter<Gateway, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void ins(const QList<GatewayInsertParameters> params) {
    GatewaySharedList newGateways;

    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<GatewayType> gatewayTypeCrud;
    gatewayTypeCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());

    for (const auto& param : params) {
      auto contract = contractCrud.selById(param.contractId);
      auto gatewayType = gatewayTypeCrud.selById(param.gatewayTypeId);
      auto node = nodeCrud.selById(param.nodeId);

      auto newGateway = GatewayShared::create();
      newGateway->setPrice(param.price);
      newGateway->setComment(param.comment);

      newGateway->setContract(contract);
      newGateway->setGatewayType(gatewayType);
      newGateway->setNode(node);

      newGateways << newGateway;
    }

    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(getSession());
    gatewayCrud.save(newGateways);
  }
};

template <template <typename> class Crud>
class Updater<Gateway, Crud> : public SessionOwner
{
public:
  template <typename... Args>
  void upd(const QList<GatewayUpdateParameters> params) {
    GatewaySharedList newGateways;

    Crud<Gateway> gatewayCrud;
    gatewayCrud.setSession(getSession());
    Crud<Contract> contractCrud;
    contractCrud.setSession(getSession());
    Crud<GatewayType> gatewayTypeCrud;
    gatewayTypeCrud.setSession(getSession());
    Crud<Node> nodeCrud;
    nodeCrud.setSession(getSession());

    for (const auto& param : params) {
      GatewayShared gateway = gatewayCrud.selById(param.gatewayId);
      gateway->setPrice(param.price);
      gateway->setComment(param.comment);

      if (gateway->getContractId() != param.contractId) {
	auto contract = contractCrud.selById(param.contractId);
	gateway->setContract(contract);
      }

      if (gateway->getGatewayTypeId() != param.gatewayTypeId) {
	auto gatewayType = gatewayTypeCrud.selById(param.gatewayTypeId);
	gateway->setGatewayType(gatewayType);
      }

      if (gateway->getNodeId() != param.nodeId) {
	auto node = nodeCrud.selById(param.nodeId);
	gateway->setNode(node);
      }
      newGateways << gateway;
    }

    gatewayCrud.save(newGateways);
  }
};

} // namespace light

#endif // GATEWAYCONTROLLER_H
