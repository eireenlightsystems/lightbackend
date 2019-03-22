#ifndef COMMANDSSCHEDULERCONTROLLERBUILDER_H
#define COMMANDSSCHEDULERCONTROLLERBUILDER_H

#include "CommandsSchedulerTypeDefs.h"
#include "MqttConnectionInfo.h"
#include "PostgresConnectionInfo.h"

namespace light {
namespace CommandsScheduler {

class CommandsSchedulerControllerBuilder
{
public:
  CommandsSchedulerControllerBuilder() = default;
  CommandsSchedulerControllerShared build();

  MqttConnectionInfo readMqttConnectionInfoFromSettings() const;
  light::PostgresConnectionInfo readDbConnectionInfoFromSettings() const;
  int readIntervalFromSettings() const;
  QString readPublisherTopicFromSettings() const;
  QString getSettingsPath() const;
};

} // namespace CommandsScheduler
} // namespace light

#endif // COMMANDSSCHEDULERCONTROLLERBUILDER_H
