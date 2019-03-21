#include "HttpServer.h"

#include "FixtureCommandRestRouter.h"
#include "FixtureGroupRouter.h"
#include "FixtureRestRouter.h"
#include "GatewayRestRouter.h"
#include "GeographRestRouter.h"
#include "NodeRestRouter.h"
#include "NodeToJson.h"
#include "TemplateRouter.h"

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
  createGeographRoutes();
  createGatewayRouters();
  createFixtureRouters();
  createFixtureGroupRouters();
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
  TemplateRouter<FixtureCommand> fixtureCommandRouter;
  fixtureCommandRouter.registerApi(httpServer);

  TemplateRouter<FixtureLightLevelCommand> fixtureLightLevelCommandRouter;
  fixtureLightLevelCommandRouter.registerApi(httpServer);

  TemplateRouter<FixtureLightSpeedCommand> fixtureLightSpeedCommandRouter;
  fixtureLightSpeedCommandRouter.registerApi(httpServer);
}

void HttpServerWrapper::createNodeRoutes() {
  TemplateRouter<Node> nodeRouter;
  nodeRouter.registerApi(httpServer);

  TemplateRouter<NodeType> nodeTypeRouter;
  nodeTypeRouter.registerApi(httpServer);
}

void HttpServerWrapper::createGeographRoutes() {
  TemplateRouter<Geograph> geographRouter;
  geographRouter.registerApi(httpServer);
}

void HttpServerWrapper::createGatewayRouters() {
  TemplateRouter<Gateway> gatewayRouter;
  gatewayRouter.registerApi(httpServer);

  TemplateRouter<EquipmentOwner> equipmentOwnerRouter;
  equipmentOwnerRouter.registerApi(httpServer);

  TemplateRouter<GatewayType> gatewayTypeRouter;
  gatewayTypeRouter.registerApi(httpServer);
}

void HttpServerWrapper::createFixtureRouters() {
  TemplateRouter<Fixture> fixtureRouter;
  fixtureRouter.registerApi(httpServer);

  TemplateRouter<FixtureType> fixtureTypeRouter;
  fixtureTypeRouter.registerApi(httpServer);

  TemplateRouter<FixtureHeightType> fixtureHeightTypeRouter;
  fixtureHeightTypeRouter.registerApi(httpServer);

  TemplateRouter<Substation> substationRouter;
  substationRouter.registerApi(httpServer);
}

void HttpServerWrapper::createFixtureGroupRouters() {
  TemplateRouter<FixtureGroup> fixtureGroupRouter;
  fixtureGroupRouter.registerApi(httpServer);

  TemplateRouter<FixtureGroupType> fixtureGroupTypeRouter;
  fixtureGroupTypeRouter.registerApi(httpServer);

  TemplateRouter<FixtureGroupOwner> ownerRouter;
  ownerRouter.registerApi(httpServer);
}

} // namespace light
