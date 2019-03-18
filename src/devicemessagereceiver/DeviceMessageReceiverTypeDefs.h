#ifndef DEVICEMESSAGERECEIVERTYPEDEFS_H
#define DEVICEMESSAGERECEIVERTYPEDEFS_H

#include <QSharedPointer>
#include "typedefs.h"

#define DeclareShared(ClassName)                       \
  class ClassName;                                     \
  using ClassName##Shared = QSharedPointer<ClassName>; \
  using ClassName##SharedList = QList<ClassName##Shared>;

DeclareShared(QMqttClient);

namespace DeviceMessageReceiver {

using ID = light::ID;

DeclareShared(MqttDeviceErrorSubscriber);
DeclareShared(AbstractDeviceErrorSaver);

} // namespace DeviceMessageReceiver

#endif // DEVICEMESSAGERECEIVERTYPEDEFS_H
