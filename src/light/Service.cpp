#include "Service.h"

#include <QDebug>

namespace light {

Service::Service(int argc, char** argv) : QtService<QCoreApplication>(argc, argv, "Light backend") {
}

void Service::start() {
  //  QCoreApplication *app = application();

  mqttDatabaseProviderShared = QSharedPointer<LigthBackend>::create();
  mqttDatabaseProviderShared->init();

  httpServerWrapper = HttpServerWrapper::singleton();
  httpServerWrapper->setLightBackend(mqttDatabaseProviderShared);
  httpServerWrapper->createRoutes();
  httpServerWrapper->listen(QHostAddress::LocalHost, 8085);

  qDebug() << Q_FUNC_INFO << "started on port" << 8085;
}

} // namespace light
