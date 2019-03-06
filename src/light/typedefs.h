#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <QSharedPointer>

#define DeclareShared(ClassName)                       \
  class ClassName;                                     \
  using ClassName##Shared = QSharedPointer<ClassName>; \
  using ClassName##SharedList = QList<ClassName##Shared>;

DeclareShared(QMqttClient);

namespace light {

using ID = qulonglong;
using IDList = QList<ID>;

DeclareShared(Session);

DeclareShared(AbstractDeviceCommand);
DeclareShared(FixtureSwitchOnDeviceCommand);
DeclareShared(SpeedToLightBaseDeviceCommand);
DeclareShared(DeviceErrorSaver);
DeclareShared(MqttDeviceErrorSubscriber);
DeclareShared(CommandsScheduler);
DeclareShared(MqttDeviceCommandPublisher);
DeclareShared(SpeedToLightUpDeviceCommand);
DeclareShared(SpeedToLightDownDeviceCommand);
DeclareShared(DeviceErrorController);
DeclareShared(DeviceCommandsController);

DeclareShared(AbstractDictionaryGateway);
DeclareShared(SchedulerGateway);
DeclareShared(AbstractDeviceErrorSaver);
DeclareShared(InMemoryDatabaseGateway);
DeclareShared(InMemoryDictionaryGateway);
DeclareShared(CommandsController);
DeclareShared(SchedulerGateway);
DeclareShared(PostgresDeviceErrorSaver);
DeclareShared(Fixture);
DeclareShared(AbstractFixtureCommandFacadeGateway);
DeclareShared(AbstractFixtureGateway);
DeclareShared(AbstractFixtureLightLevelCommandGateway);
DeclareShared(AbstractFixtureLightSpeedCommandGateway);
DeclareShared(AbstractDeviceCommandGateway);

DeclareShared(FixtureCommand);
DeclareShared(FixtureLightLevelCommand);
DeclareShared(FixtureLightSpeedCommand);

DeclareShared(Node);
DeclareShared(Contragent);
DeclareShared(Contract);
DeclareShared(EquipmentType);
DeclareShared(NodeType);
DeclareShared(Geograph);

namespace PostgresqlGateway {
DeclareShared(PostgresFixtureCommandFacadeGateway);
}

} // namespace light

#endif // TYPEDEFS_H
