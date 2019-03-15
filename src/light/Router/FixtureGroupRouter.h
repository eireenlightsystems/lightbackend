#ifndef FIXTUREGROUPROUTER_H
#define FIXTUREGROUPROUTER_H

#include "FixtureGroupController.h"
#include "RestRouter.h"
#include "SimpleEditableListRouter.h"
#include "FixtureGroup.h"
#include "FixtureGroupType.h"

namespace light {

template <>
class RestRouter<FixtureGroup> : public SimpleEditableListRouter<FixtureGroup>
{
public:
  constexpr static const char* path = "/api2/fixture-group";
};

template <>
class RestRouter<FixtureGroupType> : public SimpleSelectableRouter<FixtureGroupType>
{
public:
  constexpr static const char* path = "/api2/fixture-group-type";
};

template <>
class RestRouter<FixtureGroupOwner> : public SimpleSelectableRouter<Contragent>
{
public:
  constexpr static const char* path = "/api2/fixture-group-owner";
};

} // namespace light

#endif // FIXTUREGROUPROUTER_H
