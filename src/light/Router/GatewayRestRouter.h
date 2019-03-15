#ifndef GATEWAYRESTROUTER_H
#define GATEWAYRESTROUTER_H

#include "GatewayController.h"
#include "PostgresCrudGateway.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"

namespace light {

template <>
class RestRouter<Gateway> : public SimpleEditableRouter<Gateway>
{
public:
  constexpr static const char* path = "/api2/gateway";

protected:
  QVariantHash parseUrlQuery(const QUrlQuery& urlQuery) const override {
    QVariantHash params;
    for (const auto& item : urlQuery.queryItems()) {
      params[item.first] = QVariant(item.second.toULongLong());
    }
    return params;
  }
};

template <>
class RestRouter<EquipmentOwner> : public SimpleSelectableRouter<EquipmentOwner>
{
public:
  constexpr static const char* path = "/api2/gateway-owner";
};

template <>
class RestRouter<GatewayType> : public SimpleSelectableRouter<GatewayType>
{
public:
  constexpr static const char* path = "/api2/gateway-type";
};

} // namespace light

#endif // GATEWAYRESTROUTER_H
