#ifndef SERVICE_H
#define SERVICE_H

#include "HttpServer.h"
#include "LigthBackend.h"

#include <qtservice.h>

namespace light {

class Service : public QtService<QCoreApplication>
{
public:
  Service(int argc, char** argv);
  ~Service() override = default;
  void start() override;

private:
  QSharedPointer<HttpServerWrapper> httpServerWrapper;
  QSharedPointer<LigthBackend> mqttDatabaseProviderShared;
};

} // namespace light
#endif // SERVICE_H
