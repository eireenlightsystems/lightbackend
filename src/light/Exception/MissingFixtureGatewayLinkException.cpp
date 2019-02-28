#include "MissingFixtureGatewayLinkException.h"

namespace light {
MissingFixtureGatewayLinkException::MissingFixtureGatewayLinkException(ID fixtureId)
  : BadInputDataException(QString("Светильник с идентификатором '%1' не привязан к шлюзу").arg(fixtureId)) {
}

MissingFixtureGatewayLinkException* MissingFixtureGatewayLinkException::clone() const {
  return new MissingFixtureGatewayLinkException(*this);
}
} // namespace light
