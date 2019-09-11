#include "HttpServer.h"

#include "AuthRouter.h"
#include "ContractRestRouter.h"
#include "ContractTypeRestRouter.h"
#include "FixtureCommandRestRouter.h"
#include "FixtureGroupRouter.h"
#include "FixtureRestRouter.h"
#include "FixtureTypeRestRouter.h"
#include "GatewayRestRouter.h"
#include "GeographRestRouter.h"
#include "GeographFiasRestRouter.h"
#include "NodeRestRouter.h"
#include "NodeToJson.h"
#include "SensorRouter.h"
#include "NodeTypeRestRouter.h"
#include "SensorTypeRestRouter.h"
#include "GatewayTypeRestRouter.h"
#include "CompanyDepartmentRestRouter.h"
#include "PersonRestRouter.h"
#include "SubstationRestRouter.h"
#include "UserRestRouter.h"
#include "RoleRestRouter.h"
#include "ComponentRestRouter.h"
#include "RolerightRestRouter.h"

namespace light {
HttpServerWrapper::HttpServerWrapper(QObject* parent) : QObject(parent) {
}

QSharedPointer<HttpServerWrapper> HttpServerWrapper::singleton() {
  static QSharedPointer<HttpServerWrapper> wrapper = QSharedPointer<HttpServerWrapper>::create();
  return wrapper;
}

void HttpServerWrapper::createRoutes() {
  createAuthRoutes();
  createCommandsRoutes();
  createNodeRoutes();
  createGatewayRouters();
  createFixtureRouters();
  createFixtureGroupRouters();
  createSensorRouters();
  createContractRouters();
  createDictionaryRouters();
  createAdminRoutes();
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

bool HttpServerWrapper::isLoggedIn(const QString& token) const {
  return lightBackendShared->isLoggedIn(token);
}

void HttpServerWrapper::createAuthRoutes() {
  AuthRouter router;
  router.registerApi(httpServer);
}

void HttpServerWrapper::createCommandsRoutes() {
  RestRouter<FixtureCommand> fixtureCommandRouter;
  fixtureCommandRouter.registerApi(httpServer);

  RestRouter<FixtureCommandStatus> fixtureCommandStatusRouter;
  fixtureCommandStatusRouter.registerApi(httpServer);

  RestRouter<FixtureLightLevelCommand> fixtureLightLevelCommandRouter;
  fixtureLightLevelCommandRouter.registerApi(httpServer);

  RestRouter<FixtureLightSpeedCommand> fixtureLightSpeedCommandRouter;
  fixtureLightSpeedCommandRouter.registerApi(httpServer);

  RestRouter<FixtureLightLevelCommandType> fixtureLightLevelCommandTypeRouter;
  fixtureLightLevelCommandTypeRouter.registerApi(httpServer);

  RestRouter<FixtureLightSpeedCommandType> fixtureLightSpeedCommandTypeRouter;
  fixtureLightSpeedCommandTypeRouter.registerApi(httpServer);
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

//  RestRouter<Substation> substationRouter;
//  substationRouter.registerApi(httpServer);

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

void HttpServerWrapper::createDictionaryRouters() {
  RestRouter<Geograph> geographRouter;
  geographRouter.registerApi(httpServer);

  RestRouter<GeographFias> geographFiasRouter;
  geographFiasRouter.registerApi(httpServer);

  RestRouter<CompanyDepartment> companyDepartmentRouter;
  companyDepartmentRouter.registerApi(httpServer);

  RestRouter<Person> personRouter;
  personRouter.registerApi(httpServer);

  RestRouter<Substation> substationRouter;
  substationRouter.registerApi(httpServer);
}

void HttpServerWrapper::createContractRouters() {
  RestRouter<Contract> contractRouter;
  contractRouter.registerApi(httpServer);

  RestRouter<ContractType> contractTypeRouter;
  contractTypeRouter.registerApi(httpServer);

}

void HttpServerWrapper::createAdminRoutes() {
  RestRouter<User> userRouter;
  userRouter.registerApi(httpServer);

  RestRouter<Role> RoleRouter;
  RoleRouter.registerApi(httpServer);

  RestRouter<Component> componentRouter;
  componentRouter.registerApi(httpServer);

  RestRouter<Roleright> rolerightRouter;
  rolerightRouter.registerApi(httpServer);
}

} // namespace light
