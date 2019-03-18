#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <QSharedPointer>

#define DeclareShared(ClassName)                       \
  class ClassName;                                     \
  using ClassName##Shared = QSharedPointer<ClassName>; \
  using ClassName##SharedList = QList<ClassName##Shared>;

DeclareShared(QMqttClient);

namespace DeviceMessageReceiver {

using ID = qulonglong;

DeclareShared(MqttDeviceErrorSubscriber);
DeclareShared(AbstractDeviceErrorSaver);

}

#endif // TYPEDEFS_H
