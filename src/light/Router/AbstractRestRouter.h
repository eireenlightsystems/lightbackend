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

  static QJsonDocument errorStringToJson(const char* error);
  static QJsonDocument errorStringToJson(const QString& error);

protected:
  template <typename RouteFunction, typename... Args>
  static QHttpServerResponse baseRouteFunction(RouteFunction routeFunction, Args&&... args);
};

template <typename RouteFunction, typename... Args>
QHttpServerResponse AbstractRestRouter::baseRouteFunction(RouteFunction routeFunction, Args&&... args) {
  QHttpServerResponder::StatusCode statusCode = QHttpServerResponder::StatusCode::Ok;
  QJsonDocument jsonDocument;
  try {
    auto provider = HttpServerWrapper::singleton();
    if (!provider->isLoggedIn()) {
      return QHttpServerResponse(QHttpServerResponder::StatusCode::Unauthorized);
    }
    return routeFunction(std::forward<Args>(args)...);
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
