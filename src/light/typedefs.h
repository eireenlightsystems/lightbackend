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

DeclareShared(FixtureCommand);
DeclareShared(FixtureLightLevelCommand);
DeclareShared(FixtureLightSpeedCommand);

DeclareShared(Node);
DeclareShared(NodeType);
DeclareShared(NodeContract);
DeclareShared(NodeOwner);

DeclareShared(Contragent);
DeclareShared(Contract);
DeclareShared(EquipmentType);

DeclareShared(Geograph);
DeclareShared(Gateway);
DeclareShared(GatewayContract);
DeclareShared(GatewayType);

DeclareShared(EquipmentOwner);

DeclareShared(Fixture);
DeclareShared(FixtureType);
DeclareShared(FixtureHeightType);
DeclareShared(FixtureOwner);
DeclareShared(FixtureContract);

DeclareShared(Substation);

DeclareShared(FixtureGroup);
DeclareShared(FixtureGroupType);
DeclareShared(FixtureGroupOwner);

DeclareShared(Sensor);
DeclareShared(SensorType);
DeclareShared(SensorContract);
DeclareShared(SensorOwner);

} // namespace light

#endif // TYPEDEFS_H
