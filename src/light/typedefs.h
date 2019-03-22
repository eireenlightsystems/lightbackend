#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <QSharedPointer>

#define DeclareShared(ClassName)                       \
  class ClassName;                                     \
  using ClassName##Shared = QSharedPointer<ClassName>; \
  using ClassName##SharedList = QList<ClassName##Shared>;

namespace light {

using ID = qulonglong;
using IDList = QList<ID>;

DeclareShared(Session);
DeclareShared(Fixture);
DeclareShared(FixtureCommand);
DeclareShared(FixtureLightLevelCommand);
DeclareShared(FixtureLightSpeedCommand);

DeclareShared(Node);
DeclareShared(Contragent);
DeclareShared(Contract);
DeclareShared(EquipmentType);
DeclareShared(NodeType);
DeclareShared(Geograph);
DeclareShared(Gateway);
DeclareShared(EquipmentOwner);
DeclareShared(GatewayType);
DeclareShared(FixtureType);
DeclareShared(FixtureHeightType);
DeclareShared(Substation);
DeclareShared(FixtureGroup);
DeclareShared(FixtureGroupType);
DeclareShared(FixtureGroupOwner);

} // namespace light

#endif // TYPEDEFS_H
