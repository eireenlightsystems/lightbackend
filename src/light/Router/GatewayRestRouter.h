#ifndef GATEWAYRESTROUTER_H
#define GATEWAYRESTROUTER_H

#include "Gateway.h"
#include "GatewayContractToJson.h"
#include "GatewayController.h"
#include "GatewayOwnerToJson.h"
#include "GatewayToJson.h"
#include "GatewayTypeToJson.h"
#include "NodeController.h"
#include "NodeToJson.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudGateway.h"
#include "PostgresCrudGatewayContract.h"
#include "PostgresCrudGatewayType.h"
#include "PostgresCrudNode.h"
#include "RestRouter.h"
#include "SimpleEditableListRouter.h"

namespace light {

template <>
class RestRouter<Gateway> : public SimpleEditableListRouter<Gateway>
{
public:
  QString getName() const override {
    return "gateways";
  }

  QString getChildItemName() const override {
    return "nodes";
  }

  QHttpServerResponse getListItems(ID listId) override {
    return getListItemsHelper<Node>(listId, "gatewayId");
  }
};

template <>
class RestRouter<EquipmentOwner> : public SimpleSelectableRouter<EquipmentOwner>
{
public:
  QString getName() const override {
    return "gateways-owners";
  }
};

template <>
class RestRouter<GatewayContract> : public SimpleSelectableRouter<GatewayContract>
{
public:
  QString getName() const override {
    return "gateways-contracts";
  }
};

} // namespace light

#endif // GATEWAYRESTROUTER_H
