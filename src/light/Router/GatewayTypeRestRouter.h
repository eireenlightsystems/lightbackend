#ifndef GATEWAYTYPERESTROUTER_H
#define GATEWAYTYPERESTROUTER_H

#include "GatewayType.h"
#include "GatewayTypeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudGatewayType.h"

namespace light {

template <>
class RestRouter<GatewayType> : public SimpleEditableRouter<GatewayType>
{
public:
  QString getName() const override {
    return "gateways-types";
  }
};

}

#endif // GATEWAYTYPERESTROUTER_H
