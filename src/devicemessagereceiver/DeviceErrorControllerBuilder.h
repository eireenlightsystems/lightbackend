#ifndef DEVICEERRORCONTROLLERBUILDER_H
#define DEVICEERRORCONTROLLERBUILDER_H

#include "DeviceMessageReceiverTypeDefs.h"
#include "MqttConnectionInfo.h"
#include "PostgresConnectionInfo.h"

namespace light {
namespace DeviceMessageReceiver {

class DeviceErrorControllerBuilder
{
public:
  DeviceErrorControllerBuilder() = default;
  DeviceErrorControllerShared build();
  light::PostgresConnectionInfo readDbConnectionInfoFromSettings() const;
  MqttConnectionInfo readMqttConnectionInfoFromSettings() const;
  QString readSubscriberTopicFromSettings() const;
  QString getSettingsPath() const;
};

} // namespace DeviceMessageReceiver
} // namespace light

#endif // DEVICEERRORCONTROLLERBUILDER_H
