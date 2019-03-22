#ifndef DEVICEMESSAGERECEIVERTYPEDEFS_H
#define DEVICEMESSAGERECEIVERTYPEDEFS_H

#include "typedefs.h"

DeclareShared(QMqttClient);

namespace light {
namespace DeviceMessageReceiver {

DeclareShared(MqttDeviceErrorSubscriber);
DeclareShared(AbstractDeviceErrorSaver);
DeclareShared(DeviceErrorController);
DeclareShared(PostgresDeviceErrorSaver);

} // namespace DeviceMessageReceiver
} // namespace light

#endif // DEVICEMESSAGERECEIVERTYPEDEFS_H
