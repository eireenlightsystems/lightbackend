#include "CommandsScheduler.h"
#include "SchedulerGateway.h"

#include <QDebug>

namespace light {
CommandsScheduler::CommandsScheduler(QObject* parent) : QObject(parent) {
  connect(&checkCommandTimer, &QTimer::timeout, [this]() { emit timeout(checkCommandDateTime); });
  checkCommandTimer.setSingleShot(true);
}

void CommandsScheduler::setTimer(const QDateTime& datetime) {
  if (checkCommandDateTime != datetime) {
//    qDebug() << "current date time" << checkCommandDateTime.toString("dd.MM.yy hh:mm") << "new date time"
//	     << datetime.toString("dd.MM.yy hh:mm");
    checkCommandDateTime = datetime;
    checkCommandTimer.stop();
    if (checkCommandDateTime.isValid()) {
      auto interval = QDateTime::currentDateTime().msecsTo(checkCommandDateTime);
      interval = qMax(interval, qint64(0));
      checkCommandTimer.start(interval);
    }
  }
}

SchedulerGatewayShared CommandsScheduler::getSchedulerGateway() const {
  return schedulerGateway;
}

void CommandsScheduler::setSchedulerGateway(const SchedulerGatewayShared& value) {
  schedulerGateway = value;
}

void CommandsScheduler::checkUpdates() {
  setTimer(schedulerGateway->getClosestCommandDateTime());
}

QDateTime CommandsScheduler::getCheckCommandDateTime() const {
  return checkCommandDateTime;
}
} // namespace light
