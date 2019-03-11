#ifndef JSONTOFIXTUREGROUP_H
#define JSONTOFIXTUREGROUP_H

#include "FromJsonConverter.h"
#include "FixtureGroupController.h"

namespace light {

template<>
FixtureGroupInsertParameters FromJsonConverter<FixtureGroupInsertParameters>::parse(const QJsonObject& jsonObject);

template<>
FixtureGroupUpdateParameters FromJsonConverter<FixtureGroupUpdateParameters>::parse(const QJsonObject& jsonObject);
} // namespace light

#endif // JSONTOFIXTUREGROUP_H
