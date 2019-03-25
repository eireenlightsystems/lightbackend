#ifndef GATEWAYRESTROUTER_H
#define GATEWAYRESTROUTER_H

#include "GatewayController.h"
#include "GatewayOwnerToJson.h"
#include "GatewayToJson.h"
#include "GatewayTypeToJson.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudGateway.h"
#include "PostgresCrudGatewayType.h"
#include "RestRouter.h"
#include "SimpleEditableListRouter.h"
#include "NodeToJson.h"
#include "PostgresCrudNode.h"
#include "NodeController.h"

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
class RestRouter<GatewayType> : public SimpleSelectableRouter<GatewayType>
{
public:
  QString getName() const override {
    return "gateways-types";
  }
};

} // namespace light

#endif // GATEWAYRESTROUTER_H
