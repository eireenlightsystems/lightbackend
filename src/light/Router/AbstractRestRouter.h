#ifndef ABSTRACTRESTROUTER_H
#define ABSTRACTRESTROUTER_H

#include "BadInputDataException.h"
#include "BadRequestException.h"
#include "DatabaseException.h"
#include "HttpServer.h"
#include "typedefs.h"

#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <functional>

namespace light {

class AbstractRestRouter
{
public:
  virtual ~AbstractRestRouter() = 0;
  virtual void registerApi(QHttpServer& httpServer) const = 0;
  virtual QString getName() const = 0;
  QString getFullName() const {
    return routerPrefixString + "/" + getName();
  }
  QString getIdFullName() const {
    return getFullName() + "/" + "<arg>";
  }

  static QJsonDocument errorStringToJson(const char* error);
  static QJsonDocument errorStringToJson(const QString& error);

  template <typename RouteFunction, typename... Args>
  static QHttpServerResponse baseRouteFunction(RouteFunction routeFunction, Args&&... args);

protected:
  const QString routerPrefixString = "/api/v1";
};

template <typename RouteFunction, typename... Args>
QHttpServerResponse AbstractRestRouter::baseRouteFunction(RouteFunction routeFunction, Args&&... args) {
  QHttpServerResponder::StatusCode statusCode = QHttpServerResponder::StatusCode::Ok;
  QJsonDocument jsonDocument;
  try {
    auto httpServerWrapper = HttpServerWrapper::singleton();
    if (!httpServerWrapper->isLoggedIn()) {
      return QHttpServerResponse(QHttpServerResponder::StatusCode::Unauthorized);
    }
    auto session = httpServerWrapper->getLightBackend()->getSession();
    return routeFunction(session, std::forward<Args>(args)...);
  } catch (const BadRequestException& badRequest) {
    jsonDocument = AbstractRestRouter::errorStringToJson(badRequest.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::BadRequest;
  } catch (const BadInputDataException& exeption) {
    jsonDocument = AbstractRestRouter::errorStringToJson(exeption.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::BadRequest;
  } catch (const DatabaseException& exeption) {
    jsonDocument = AbstractRestRouter::errorStringToJson(exeption.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::InternalServerError;
  } catch (const Exception& exeption) {
    jsonDocument = AbstractRestRouter::errorStringToJson(exeption.getErrorText());
    statusCode = QHttpServerResponder::StatusCode::InternalServerError;
  } catch (...) {
    jsonDocument = AbstractRestRouter::errorStringToJson(QString("Unknown error"));
    statusCode = QHttpServerResponder::StatusCode::InternalServerError;
  }
  return QHttpServerResponse("text/json", jsonDocument.toJson(), statusCode);
}
} // namespace light

#endif // ABSTRACTRESTROUTER_H
