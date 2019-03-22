#ifndef MQTTCONNECTIONINFO_H
#define MQTTCONNECTIONINFO_H

#include <QString>

namespace light {
namespace DeviceMessageReceiver {

struct MqttConnectionInfo
{
  QString hostName;
  quint16 port;
  QString clientId;
};

} // namespace DeviceMessageReceiver
} // namespace light

#endif // MQTTCONNECTIONINFO_H
