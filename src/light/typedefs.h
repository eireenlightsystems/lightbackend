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
DeclareShared(FixtureCommandStatus);
DeclareShared(FixtureLightLevelCommand);
DeclareShared(FixtureLightSpeedCommand);
DeclareShared(FixtureCommandType);
DeclareShared(FixtureLightLevelCommandType);
DeclareShared(FixtureLightSpeedCommandType);

DeclareShared(Node);
DeclareShared(NodeContract);
DeclareShared(NodeOwner);

DeclareShared(Geograph);
DeclareShared(GeographFias);
DeclareShared(Gateway);
DeclareShared(GatewayContract);

DeclareShared(EquipmentOwner);

DeclareShared(Fixture);
DeclareShared(FixtureInGroup);
DeclareShared(FixtureHeightType);
DeclareShared(FixtureOwner);
DeclareShared(FixtureContract);
DeclareShared(FixtureInstaller);

DeclareShared(FixtureGroup);
DeclareShared(FixtureGroupType);
DeclareShared(FixtureGroupOwner);

DeclareShared(Sensor);
DeclareShared(SensorContract);
DeclareShared(SensorOwner);

DeclareShared(EquipmentType);
DeclareShared(NodeType);
DeclareShared(FixtureType);
DeclareShared(SensorType);
DeclareShared(GatewayType);

DeclareShared(Contragent);
DeclareShared(CompanyDepartment);
DeclareShared(Person);
DeclareShared(Substation);

DeclareShared(Contract);
DeclareShared(ContractType);

DeclareShared(User);
DeclareShared(UserInRole);
DeclareShared(Role);
DeclareShared(RoleInUser);
DeclareShared(Component);
DeclareShared(Roleright);
} // namespace light

#endif // TYPEDEFS_H
