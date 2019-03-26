#include "GatewayContractToJson.h"

#include "ContractToJson.h"

namespace light {

QJsonObject ToJsonConverter<GatewayContract>::toJson(const GatewayContractShared& gatewayContract) const {
  ToJsonConverter<Contract> contractConverter;
  return contractConverter.toJson(gatewayContract.dynamicCast<Contract>());
}

} // namespace light
