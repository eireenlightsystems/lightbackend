#ifndef COMMANDSSCHEDULER_H
#define COMMANDSSCHEDULER_H

#include "typedefs.h"

#include <QDateTime>
#include <QObject>
#include <QTimer>

namespace light {

class AbstractDeviceCommand;

class CommandsScheduler : public QObject
{
  Q_OBJECT
public:
  explicit CommandsScheduler(QObject* parent = nullptr);

  QDateTime getCheckCommandDateTime() const;

  SchedulerGatewayShared getSchedulerGateway() const;
  void setSchedulerGateway(const SchedulerGatewayShared &value);

signals:
  void timeout(const QDateTime&) const;

public slots:
  void checkUpdates();
  void setTimer(const QDateTime& datetime);

private:
  SchedulerGatewayShared schedulerGateway;
  QDateTime checkCommandDateTime;
  QTimer checkCommandTimer;
};
} // namespace light

#endif // COMMANDSSCHEDULER_H
