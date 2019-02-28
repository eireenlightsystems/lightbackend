#ifndef MISSINGFIXTUREGATEWAYLINKEXCEPTION_H
#define MISSINGFIXTUREGATEWAYLINKEXCEPTION_H

#include "BadInputDataException.h"

namespace light {
class MissingFixtureGatewayLinkException : public BadInputDataException
{
public:
  explicit MissingFixtureGatewayLinkException(ID fixtureId);
  MissingFixtureGatewayLinkException* clone() const override;
};
} // namespace light

#endif // MISSINGFIXTUREGATEWAYLINKEXCEPTION_H
