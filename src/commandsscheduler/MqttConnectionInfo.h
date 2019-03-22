#ifndef MQTTCONNECTIONINFO_H
#define MQTTCONNECTIONINFO_H

#include <QString>

namespace light {
namespace CommandsScheduler {

struct MqttConnectionInfo
{
  QString hostName;
  quint16 port;
  QString clientId;
};

} // namespace CommandsScheduler
} // namespace light

#endif // MQTTCONNECTIONINFO_H
