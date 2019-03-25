#ifndef FIXTUREGROUPROUTER_H
#define FIXTUREGROUPROUTER_H

#include "ContragentToJson.h"
#include "FixtureGroup.h"
#include "FixtureGroupController.h"
#include "FixtureGroupOwnerToJson.h"
#include "FixtureGroupToJson.h"
#include "FixtureGroupType.h"
#include "FixtureGroupTypeToJson.h"
#include "PostgresCrudFixtureGroup.h"
#include "PostgresCrudFixtureGroupOwner.h"
#include "PostgresCrudFixtureGroupType.h"
#include "RestRouter.h"
#include "SimpleEditableListRouter.h"
#include "FixtureController.h"

namespace light {

template <>
class RestRouter<FixtureGroup> : public SimpleEditableListRouter<FixtureGroup>
{
public:
  QString getName() const override {
    return "fixtures-groups";
  }

  QString getChildItemName() const override {
    return "fixtures";
  }

  QHttpServerResponse getListItems(ID listId) override {
    return getListItemsHelper<Fixture>(listId, "groupId");
  }
};

template <>
class RestRouter<FixtureGroupType> : public SimpleSelectableRouter<FixtureGroupType>
{
public:
  QString getName() const override {
    return "fixtures-groups-types";
  }
};

template <>
class RestRouter<FixtureGroupOwner> : public SimpleSelectableRouter<FixtureGroupOwner>
{
public:
  QString getName() const override {
    return "fixtures-groups-owners";
  }
};

} // namespace light

#endif // FIXTUREGROUPROUTER_H
