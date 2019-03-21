#include "Service.h"

#include <QCoreApplication>
#include <QDir>
#include <QSettings>

#ifdef LOG_TO_SYSLOG
#include <QtGlobal>
#include <syslog.h>

static void syslogMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message) {
  QString formattedMessage = qFormatLogMessage(type, context, message);
  int priority = LOG_INFO; // Informational
  switch (type) {
    case QtDebugMsg:
      priority = LOG_DEBUG; // Debug-level messages
      break;
    case QtInfoMsg:
      priority = LOG_INFO; // Informational conditions
      break;
    case QtWarningMsg:
      priority = LOG_WARNING; // Warning conditions
      break;
    case QtCriticalMsg:
      priority = LOG_CRIT; // Critical conditions
      break;
    case QtFatalMsg:
      priority = LOG_ALERT; // Action must be taken immediately
      break;
  }
  syslog(priority, "%s", formattedMessage.toUtf8().constData());
}
#endif

int main(int argc, char* argv[]) {
#ifdef LOG_TO_SYSLOG
  qInstallMessageHandler(syslogMessageHandler);
#endif
  QString tmpPath = QDir::tempPath();
  QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, tmpPath);
  CommandsScheduler::Service service(argc, argv);
  return service.exec();
}
