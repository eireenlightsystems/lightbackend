#ifndef NODERESTROUTER_H
#define NODERESTROUTER_H

#include "ContainersRegistrationHelpers.h"
#include "FixtureController.h"
#include "GatewayController.h"
#include "NodeController.h"
#include "NodeToJson.h"
#include "NodeTypeToJson.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudGeograph.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudNodeType.h"
#include "RestRouter.h"
#include "SimpleEditableListRouter.h"
#include "FixtureController.h"
#include "SensorToJson.h"
#include "GatewayToJson.h"
#include "FixtureToJson.h"

namespace light {

template <>
class RestRouter<Node> : public SimpleEditableRouter<Node>
{
public:
  RestRouter() = default;
  ~RestRouter() override = default;
  QString getName() const override {
    return "nodes";
  }

  void registerApi(QHttpServer& httpServer) const override {
    SimpleEditableRouter<Node>::registerApi(httpServer);
    registerFixtures(httpServer);
    registerGateways(httpServer);
    registerSensors(httpServer);
  }

  QHttpServerResponse getFixtures(ID nodeId) {
    return getListItemsHelper<Fixture>(nodeId, "nodeId");
  }

  QHttpServerResponse addFixture(ID nodeId, ID fixtureId) {
    return oneItemActionTemplate(&Controller<Node, CRUD>::addFixtures, nodeId, fixtureId);
  }

  QHttpServerResponse addFixtures(const QHttpServerRequest& req, ID nodeId) {
    return itemsActionTemplate(&Controller<Node, CRUD>::addFixtures, req, nodeId);
  }

  QHttpServerResponse delFixture(ID nodeId, ID fixtureId) {
    return oneItemActionTemplate(&Controller<Node, CRUD>::delFixtures, nodeId, fixtureId);
  }

  QHttpServerResponse delFixtures(const QHttpServerRequest& req, ID nodeId) {
    return itemsActionTemplate(&Controller<Node, CRUD>::delFixtures, req, nodeId);
  }

  QHttpServerResponse getGateways(ID nodeId) {
    return getListItemsHelper<Gateway>(nodeId, "nodeId");
  }

  QHttpServerResponse addGateway(ID nodeId, ID gatewayId) {
    return oneItemActionTemplate(&Controller<Node, CRUD>::addGateways, nodeId, gatewayId);
  }

  QHttpServerResponse addGateways(const QHttpServerRequest& req, ID nodeId) {
    return itemsActionTemplate(&Controller<Node, CRUD>::addGateways, req, nodeId);
  }

  QHttpServerResponse delGateway(ID nodeId, ID gatewayId) {
    return oneItemActionTemplate(&Controller<Node, CRUD>::delGateways, nodeId, gatewayId);
  }

  QHttpServerResponse delGateways(const QHttpServerRequest& req, ID nodeId) {
    return itemsActionTemplate(&Controller<Node, CRUD>::delGateways, req, nodeId);
  }

  QHttpServerResponse getSensors(ID nodeId) {
    return getListItemsHelper<Sensor>(nodeId, "nodeId");
  }

  QHttpServerResponse addSensor(ID nodeId, ID sersorId) {
    return oneItemActionTemplate(&Controller<Node, CRUD>::addSensors, nodeId, sersorId);
  }

  QHttpServerResponse addSensors(const QHttpServerRequest& req, ID nodeId) {
    return itemsActionTemplate(&Controller<Node, CRUD>::addSensors, req, nodeId);
  }

  QHttpServerResponse delSensor(ID nodeId, ID sersorId) {
    return oneItemActionTemplate(&Controller<Node, CRUD>::delSensors, nodeId, sersorId);
  }

  QHttpServerResponse delSensors(const QHttpServerRequest& req, ID nodeId) {
    return itemsActionTemplate(&Controller<Node, CRUD>::delSensors, req, nodeId);
  }

private:
  void registerFixtures(QHttpServer& httpServer) const {
    RegisterGetHelper(Node, "fixtures", getFixtures);

    RegisterAddOneItemHelper(Node, "fixtures", addFixture);
    RegisterAddItemsHelper(Node, "fixtures", addFixtures);

    RegisterDeleteOneItemHelper(Node, "fixtures", delFixture);
    RegisterDeleteItemsHelper(Node, "fixtures", delFixtures);
  }

  void registerGateways(QHttpServer& httpServer) const {
    RegisterGetHelper(Node, "gateways", getGateways);

    RegisterAddOneItemHelper(Node, "gateways", addGateway);
    RegisterAddItemsHelper(Node, "gateways", addGateways);

    RegisterDeleteOneItemHelper(Node, "gateways", delGateway);
    RegisterDeleteItemsHelper(Node, "gateways", delGateways);
  }

  void registerSensors(QHttpServer& httpServer) const {
    RegisterGetHelper(Node, "sensors", getSensors);

    RegisterAddOneItemHelper(Node, "sensors", addSensor);
    RegisterAddItemsHelper(Node, "sensors", addSensors);

    RegisterDeleteOneItemHelper(Node, "sensors", delSensor);
    RegisterDeleteItemsHelper(Node, "sensors", delSensors);
  }

  template <typename ChildType>
  QHttpServerResponse getListItemsHelper(ID listId, const QString& paramName) {
    const QVariantHash params{
	{paramName, listId},
    };

    Controller<ChildType, CRUD> controller;
    controller.setSession(this->getSession());
    auto objects = controller.sel(params);

    ToJsonConverter<ChildType> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

  QHttpServerResponse
  oneItemActionTemplate(void (Controller<Node, CRUD>::*action)(ID, const IDList&), ID nodeId, const ID idItem) {
    auto controller = this->createController();
    (controller.*action)(nodeId, {idItem});
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  QHttpServerResponse
  itemsActionTemplate(void (Controller<Node, CRUD>::*action)(ID, const IDList&), const QHttpServerRequest& req, ID nodeId) {
    JsonToIds converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto ids = converter.getIds();
    auto controller = this->createController();
    (controller.*action)(nodeId, ids);
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }
};

template <>
class RestRouter<NodeType> : public SimpleSelectableRouter<NodeType>
{
public:
  QString getName() const override {
    return "nodes-types";
  }
};

} // namespace light

#endif // NODERESTROUTER_H
