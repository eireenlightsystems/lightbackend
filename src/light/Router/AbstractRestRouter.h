#ifndef ABSTRACTRESTROUTER_H
#define ABSTRACTRESTROUTER_H

#include "typedefs.h"

#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <functional>

#include "BadInputDataException.h"
#include "BadRequestException.h"
#include "DatabaseException.h"
#include "HttpServer.h"

#include <QJsonDocument>

namespace light {

class AbstractRestRouter
{
public:
  virtual ~AbstractRestRouter() = 0;
  virtual QHttpServerResponse get(const SessionShared& session, const QHttpServerRequest& req) const = 0;
  virtual QHttpServerResponse post(const SessionShared& session, const QHttpServerRequest& req) const = 0;
  virtual QHttpServerResponse patch(const SessionShared& session, const QHttpServerRequest& req) const = 0;
  virtual QHttpServerResponse del(const SessionShared& session, const QHttpServerRequest& req) const = 0;
  virtual QHttpServerResponse delById(const SessionShared& session, ID id) const = 0;

  virtual QHttpServerResponse addItemToList(const SessionShared& session, ID listId, ID itemId) const = 0;
  virtual QHttpServerResponse delItemFromList(const SessionShared& session, ID listId, ID itemId) const = 0;
  virtual void registerApi(QHttpServer& httpServer) const = 0;

  virtual QString getPath() const = 0;

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
} // namespace light

#endif // ABSTRACTRESTROUTER_H
