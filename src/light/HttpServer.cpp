#include "HttpServer.h"

#include "ContractRouter.h"
#include "FixtureCommandRestRouter.h"
#include "FixtureGroupRouter.h"
#include "FixtureRestRouter.h"
#include "GatewayRestRouter.h"
#include "GeographRestRouter.h"
#include "NodeRestRouter.h"
#include "NodeToJson.h"
#include "SensorRouter.h"

namespace light {
HttpServerWrapper::HttpServerWrapper(QObject* parent) : QObject(parent) {
}

QSharedPointer<HttpServerWrapper> HttpServerWrapper::singleton() {
  static QSharedPointer<HttpServerWrapper> wrapper = QSharedPointer<HttpServerWrapper>::create();
  return wrapper;
}

void HttpServerWrapper::createRoutes() {
  createCommandsRoutes();
  createNodeRoutes();
  createGatewayRouters();
  createFixtureRouters();
  createFixtureGroupRouters();
  createSensorRouters();
  createDictionary();
}

void HttpServerWrapper::listen(const QHostAddress& address, quint16 port) {
  httpServer.listen(address, port);
}

QSharedPointer<LigthBackend> HttpServerWrapper::getLightBackend() const {
  return lightBackendShared;
}

void HttpServerWrapper::setLightBackend(const QSharedPointer<LigthBackend>& value) {
  lightBackendShared = value;
}

bool HttpServerWrapper::isLoggedIn() const {
  return true;
}

void HttpServerWrapper::createCommandsRoutes() {
  RestRouter<FixtureCommand> fixtureCommandRouter;
  fixtureCommandRouter.registerApi(httpServer);

  RestRouter<FixtureLightLevelCommand> fixtureLightLevelCommandRouter;
  fixtureLightLevelCommandRouter.registerApi(httpServer);

  RestRouter<FixtureLightSpeedCommand> fixtureLightSpeedCommandRouter;
  fixtureLightSpeedCommandRouter.registerApi(httpServer);
}

void HttpServerWrapper::createNodeRoutes() {
  RestRouter<Node> nodeRouter;
  nodeRouter.registerApi(httpServer);

  RestRouter<NodeType> nodeTypeRouter;
  nodeTypeRouter.registerApi(httpServer);

  RestRouter<NodeContract> nodeContractRouter;
  nodeContractRouter.registerApi(httpServer);

  RestRouter<NodeOwner> nodeOwnerRouter;
  nodeOwnerRouter.registerApi(httpServer);
}

void HttpServerWrapper::createGatewayRouters() {
  RestRouter<Gateway> gatewayRouter;
  gatewayRouter.registerApi(httpServer);

  RestRouter<EquipmentOwner> equipmentOwnerRouter;
  equipmentOwnerRouter.registerApi(httpServer);

  RestRouter<GatewayType> gatewayTypeRouter;
  gatewayTypeRouter.registerApi(httpServer);

  RestRouter<GatewayContract> gatewayContractRouter;
  gatewayContractRouter.registerApi(httpServer);
}

void HttpServerWrapper::createFixtureRouters() {
  RestRouter<Fixture> fixtureRouter;
  fixtureRouter.registerApi(httpServer);

  RestRouter<FixtureType> fixtureTypeRouter;
  fixtureTypeRouter.registerApi(httpServer);

  RestRouter<FixtureHeightType> fixtureHeightTypeRouter;
  fixtureHeightTypeRouter.registerApi(httpServer);

  RestRouter<Substation> substationRouter;
  substationRouter.registerApi(httpServer);

  RestRouter<FixtureOwner> fixtureOwnerRouter;
  fixtureOwnerRouter.registerApi(httpServer);

  RestRouter<FixtureContract> fixtureContractRouter;
  fixtureContractRouter.registerApi(httpServer);

  RestRouter<FixtureInstaller> fixtureInstallerRouter;
  fixtureInstallerRouter.registerApi(httpServer);
}

void HttpServerWrapper::createFixtureGroupRouters() {
  RestRouter<FixtureGroup> fixtureGroupRouter;
  fixtureGroupRouter.registerApi(httpServer);

  RestRouter<FixtureGroupType> fixtureGroupTypeRouter;
  fixtureGroupTypeRouter.registerApi(httpServer);

  RestRouter<FixtureGroupOwner> ownerRouter;
  ownerRouter.registerApi(httpServer);
}

void HttpServerWrapper::createSensorRouters() {
  RestRouter<Sensor> sensorRouter;
  sensorRouter.registerApi(httpServer);

  RestRouter<SensorType> sensorTypeRouter;
  sensorTypeRouter.registerApi(httpServer);

  RestRouter<SensorContract> sensorContractRouter;
  sensorContractRouter.registerApi(httpServer);

  RestRouter<SensorOwner> sensorOwnerRouter;
  sensorOwnerRouter.registerApi(httpServer);
}

void HttpServerWrapper::createDictionary() {
  RestRouter<Geograph> geographRouter;
  geographRouter.registerApi(httpServer);

  RestRouter<Contract> contractRouter;
  contractRouter.registerApi(httpServer);
}

} // namespace light
