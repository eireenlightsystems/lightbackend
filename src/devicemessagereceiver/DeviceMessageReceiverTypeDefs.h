#ifndef DEVICEMESSAGERECEIVERTYPEDEFS_H
#define DEVICEMESSAGERECEIVERTYPEDEFS_H

#include "typedefs.h"

DeclareShared(QMqttClient);

namespace DeviceMessageReceiver {

using ID = light::ID;

DeclareShared(MqttDeviceErrorSubscriber);
DeclareShared(AbstractDeviceErrorSaver);
DeclareShared(DeviceErrorController);
DeclareShared(PostgresDeviceErrorSaver);

} // namespace DeviceMessageReceiver

#endif // DEVICEMESSAGERECEIVERTYPEDEFS_H
