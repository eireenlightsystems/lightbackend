#include "GatewayType.h"

namespace light {

QString GatewayType::getCommunicationStandard() const {
  return communicationStandard;
}

void GatewayType::setCommunicationStandard(QString value) {
  communicationStandard = value;
}

} // namespace light
