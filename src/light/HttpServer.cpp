#include "HttpServer.h"

#include "AbstractDeviceCommand.h"
#include "AbstractFixtureCommandGateway.h"
#include "BadInputDataException.h"
#include "BadRequestException.h"
#include "DatabaseException.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "HttpServerConverters.h"
#include "InternalServerErrorException.h"
#include "NodeRestRouter.h"
#include "NodeToJson.h"
#include "SharedTypes.h"

#include <QException>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>

namespace light {
HttpServerWrapper::HttpServerWrapper(QObject* parent) : QObject(parent) {
}

QSharedPointer<HttpServerWrapper> HttpServerWrapper::singleton() {
  static QSharedPointer<HttpServerWrapper> value = QSharedPointer<HttpServerWrapper>::create();
  return value;
}

QJsonDocument HttpServerWrapper::errorStringToJson(const char* error) {
  return errorStringToJson(QString(error));
}

QJsonDocument HttpServerWrapper::errorStringToJson(const QString& error) {
  QJsonObject errorObject;
  errorObject["message"] = error;
  QJsonDocument jsonDoc(errorObject);
  return jsonDoc;
}

void HttpServerWrapper::createRoutes() {
  createCommandsRoutes();
  createLightLevelRoutes();
  createLightSpeedRoutes();
  createNodeRoutes();
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

void HttpServerWrapper::createCommandsRoutes() {
  httpServer.route("/api2/fixture/command", QHttpServerRequest::Method::Delete, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto provider = HttpServerWrapper::singleton()->getLightBackend();
      IdsToJson converter;
      converter.convert(req.body());
      if (!converter.getIdValid()) {
	throw BadRequestException(converter.getErrorText());
      }
      auto deleteCommands = converter.getIds();
      provider->deleteFixturesCommands(deleteCommands);
      return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
    };
    return baseRouteFunction(routeFunction, req);
  });
}

void HttpServerWrapper::createLightLevelRoutes() {
  httpServer.route(
      "/api2/fixture/command/lightlevel", QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
	auto routeFunction = [](const QHttpServerRequest& req) {
	  CommandStatus commandStatus = CommandStatus(req.query().queryItemValue("statusId").toInt());
	  ID fixtureId = req.query().queryItemValue("fixtureId").toULong();
	  QString from = req.query().queryItemValue("startDateTime");
	  QString to = req.query().queryItemValue("endDateTime");

	  auto provider = HttpServerWrapper::singleton()->getLightBackend();
	  QDateTime dtFrom = QDateTime::fromString(from, Qt::ISODate);
	  if (!dtFrom.isValid()) {
	    throw BadRequestException("invalid startDateTime");
	  }
	  QDateTime dtTo = QDateTime::fromString(to, Qt::ISODate);
	  if (!dtTo.isValid()) {
	    throw BadRequestException("invalid endDateTime");
	  }
	  FixtureCommandsFilter filter{commandStatus, fixtureId, dtFrom, dtTo};
	  auto commands = provider->getFixtureLightLevelCommandsByDateTimeRange(filter);
	  FixtureLightLevelCommandsToJson converter;
	  converter.convert(commands);
	  if (!converter.getIdValid()) {
	    throw InternalServerErrorException(converter.getErrorText());
	  }
	  auto jsonDocument = converter.getJsonDocument();
	  return QHttpServerResponse("text/json", jsonDocument.toJson());
	};
	return baseRouteFunction(routeFunction, req);
      });

  httpServer.route(
      "/api2/fixture/command/lightlevel", QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
	auto routeFunction = [](const QHttpServerRequest& req) {
	  auto provider = HttpServerWrapper::singleton()->getLightBackend();
	  JsonToFixtureLightLevelCommands converter;
	  converter.convert(req.body());
	  if (!converter.getIdValid()) {
	    throw InternalServerErrorException(converter.getErrorText());
	  }
	  auto switchOnCommands = converter.getLightLevelCommands();
	  provider->switchOnFixtures(switchOnCommands);
	  return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
	};
	return baseRouteFunction(routeFunction, req);
      });
}

void HttpServerWrapper::createLightSpeedRoutes() {
  httpServer.route(
      "/api2/fixture/command/lightspeed", QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
	auto routeFunction = [](const QHttpServerRequest& req) {
	  CommandStatus commandStatus = CommandStatus(req.query().queryItemValue("statusId").toInt());
	  ID fixtureId = req.query().queryItemValue("fixtureId").toULong();
	  QString from = req.query().queryItemValue("startDateTime");
	  QString to = req.query().queryItemValue("endDateTime");
	  auto provider = HttpServerWrapper::singleton()->getLightBackend();
	  QDateTime dtFrom = QDateTime::fromString(from, Qt::ISODate);
	  if (!dtFrom.isValid()) {
	    throw BadRequestException("invalid startDateTime");
	  }
	  QDateTime dtTo = QDateTime::fromString(to, Qt::ISODate);
	  if (!dtTo.isValid()) {
	    throw BadRequestException("invalid endDateTime");
	  }
	  FixtureCommandsFilter filter{commandStatus, fixtureId, dtFrom, dtTo};
	  auto commands = provider->getFixtureLightSpeedCommandsByDateTimeRange(filter);
	  FixtureLightSpeedCommandsToJson converter;
	  converter.convert(commands);
	  if (!converter.getIdValid()) {
	    throw InternalServerErrorException(converter.getErrorText());
	  }

	  auto jsonDocument = converter.getJsonDocument();
	  return QHttpServerResponse("text/json", jsonDocument.toJson());
	};
	return baseRouteFunction(routeFunction, req);
      });

  httpServer.route(
      "/api2/fixture/command/lightspeed", QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
	auto routeFunction = [](const QHttpServerRequest& req) {
	  auto provider = HttpServerWrapper::singleton()->getLightBackend();
	  JsonToFixtureLightSpeedCommands converter;
	  converter.convert(req.body());
	  if (!converter.getIdValid()) {
	    throw InternalServerErrorException(converter.getErrorText());
	  }
	  auto lightUpSpeedCommands = converter.getLightUpSpeedCommands();
	  provider->setFixturesLightSpeed(lightUpSpeedCommands);
	  return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
	};
	return baseRouteFunction(routeFunction, req);
      });
}

void HttpServerWrapper::createNodeRoutes() {
  httpServer.route("/api2/node", QHttpServerRequest::Method::Get, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      return NodeRestRouter::get(session, req);
    };
    return baseRouteFunction(routeFunction, req);
  });
  httpServer.route("/api2/node", QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      return NodeRestRouter::post(session, req);
    };
    return baseRouteFunction(routeFunction, req);
  });
  httpServer.route("/api2/node", QHttpServerRequest::Method::Patch, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      return NodeRestRouter::patch(session, req);
    };
    return baseRouteFunction(routeFunction, req);
  });
  httpServer.route("/api2/node/coordinate", QHttpServerRequest::Method::Patch, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      return NodeRestRouter::patchSetCoordinates(session, req);
    };
    return baseRouteFunction(routeFunction, req);
  });
  httpServer.route("/api2/node", QHttpServerRequest::Method::Delete, [](const QHttpServerRequest& req) {
    auto routeFunction = [](const QHttpServerRequest& req) {
      auto session = HttpServerWrapper::singleton()->getLightBackend()->getSession();
      return NodeRestRouter::del(session, req);
    };
    return baseRouteFunction(routeFunction, req);
  });
}

template <typename RouteFunction, typename... Args>
QHttpServerResponse HttpServerWrapper::baseRouteFunction(RouteFunction routeFunction, Args&&... args) {
  QHttpServerResponder::StatusCode statusCode = QHttpServerResponder::StatusCode::Ok;
  QJsonDocument jsonDocument;
  try {
    auto provider = HttpServerWrapper::singleton();
    if (!provider->isLoggedIn()) {
      return QHttpServerResponse(QHttpServerResponder::StatusCode::Unauthorized);
    }
    return routeFunction(std::forward<Args>(args)...);
  } catch (const BadRequestException& badRequest) {
    jsonDocument = HttpServerWrapper::errorStringToJson(badRequest.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::BadRequest;
  } catch (const BadInputDataException& exeption) {
    jsonDocument = HttpServerWrapper::errorStringToJson(exeption.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::BadRequest;
  } catch (const DatabaseException& exeption) {
    jsonDocument = HttpServerWrapper::errorStringToJson(exeption.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::InternalServerError;
  } catch (const Exception& exeption) {
    jsonDocument = HttpServerWrapper::errorStringToJson(exeption.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::InternalServerError;
  } catch (...) {
    jsonDocument = HttpServerWrapper::errorStringToJson(QString("Unknown error"));
    statusCode = QHttpServerResponder::StatusCode::InternalServerError;
  }
  return QHttpServerResponse("text/json", jsonDocument.toJson(), statusCode);
}

bool HttpServerWrapper::isLoggedIn() const {
  return true;
}

} // namespace light
