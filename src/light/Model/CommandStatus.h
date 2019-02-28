#ifndef COMMANDSTATUS_H
#define COMMANDSTATUS_H

#include <QVariant>

namespace light {
enum CommandStatus
{
  None,
  InQueue = 3,
  Done = 5
};
}

Q_DECLARE_METATYPE(light::CommandStatus)

#endif // COMMANDSTATUS_H
