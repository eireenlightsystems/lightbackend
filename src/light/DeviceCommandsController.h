#ifndef DEVICECOMMANDSCONTROLLER_H
#define DEVICECOMMANDSCONTROLLER_H

#include "typedefs.h"

#include <QObject>

namespace light {
class DeviceCommandsController : public QObject
{
  Q_OBJECT
public:
  explicit DeviceCommandsController(QObject* parent = nullptr);
  void setCommandController(const CommandsControllerShared& commandController);

public slots:
  void setFixturesLightLevel(const FixtureLightLevelCommandSharedList& commands);
  void setFixturesLightSpeed(const FixtureLightSpeedCommandSharedList &commands);
  void deleteFixturesCommands(const QList<ID>& commands);

private:
  CommandsControllerShared commandController;
};
} // namespace light

#endif // DEVICECOMMANDSCONTROLLER_H
