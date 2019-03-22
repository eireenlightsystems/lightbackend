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
  constexpr static const char* path = "/api2/fixture";
};

template <>
class RestRouter<FixtureType> : public SimpleSelectableRouter<GatewayType>
{
public:
  constexpr static const char* path = "/api2/fixture-type";
};

template <>
class RestRouter<FixtureHeightType> : public SimpleSelectableRouter<FixtureHeightType>
{
public:
  constexpr static const char* path = "/api2/fixture-height-type";
};

template <>
class RestRouter<Substation> : public SimpleSelectableRouter<Substation>
{
public:
  constexpr static const char* path = "/api2/substation";
};

} // namespace light

#endif // FIXTURERESTROUTER_H
