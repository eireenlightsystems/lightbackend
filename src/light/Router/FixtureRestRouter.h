#ifndef FIXTURERESTROUTER_H
#define FIXTURERESTROUTER_H

#include "FixtureController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"

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
