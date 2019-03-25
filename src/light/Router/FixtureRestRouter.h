#ifndef FIXTURERESTROUTER_H
#define FIXTURERESTROUTER_H

#include "FixtureController.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudContragent.h"
#include "PostgresCrudFixture.h"
#include "PostgresCrudFixtureHeightType.h"
#include "PostgresCrudFixtureType.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudSubstation.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "FixtureToJson.h"
#include "FixtureHeightTypeToJson.h"
#include "FixtureTypeToJson.h"
#include "SubstationToJson.h"

namespace light {

template <>
class RestRouter<Fixture> : public SimpleEditableRouter<Fixture>
{
public:
  QString getName() const override {
    return "fixtures";
  }
};

template <>
class RestRouter<FixtureType> : public SimpleSelectableRouter<GatewayType>
{
public:
  QString getName() const override {
    return "fixtures-types";
  }
};

template <>
class RestRouter<FixtureHeightType> : public SimpleSelectableRouter<FixtureHeightType>
{
public:
  QString getName() const override {
    return "fixtures-height-types";
  }
};

template <>
class RestRouter<Substation> : public SimpleSelectableRouter<Substation>
{
public:
  QString getName() const override {
    return "substations";
  }
};

} // namespace light

#endif // FIXTURERESTROUTER_H
