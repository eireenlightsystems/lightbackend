#include "AuthRouter.h"

#include "BadCredentials.h"

#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>

namespace light {

void AuthRouter::registerApi(QHttpServer& httpServer) const {
  httpServer.route(getFullName() + "/login", QHttpServerRequest::Method::Post, [](const QHttpServerRequest& req) {
    QJsonParseError parseError;
    QJsonDocument jDoc = QJsonDocument::fromJson(req.body(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
      qDebug() << parseError.errorString();
      throw QHttpServerResponse(QHttpServerResponse::StatusCode::BadRequest);
    }
    QJsonObject object = jDoc.object();
    QString login = object.value("login").toString();
    QString password = object.value("password").toString();

    auto httpServerWrapper = HttpServerWrapper::singleton();
    auto backend = httpServerWrapper->getLightBackend();
    QString token;
    try {
      token = backend->login(login, password);
    } catch (const BadCredentialsException&) {
      return QHttpServerResponse(QHttpServerResponse::StatusCode::Unauthorized);
    } catch (...) {
      return QHttpServerResponse(QHttpServerResponse::StatusCode::InternalServerError);
    }

    QJsonObject responseBody;
    responseBody["token"] = token;
    QJsonDocument responseBodyDocument(responseBody);
    return QHttpServerResponse("text/json", responseBodyDocument.toJson(), QHttpServerResponse::StatusCode::Ok);
  });

  httpServer.route(getFullName() + "/logout", QHttpServerRequest::Method::Post, []() {
    auto httpServerWrapper = HttpServerWrapper::singleton();
    auto backend = httpServerWrapper->getLightBackend();
    const QString token = "";
    backend->logout(token);
    return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
  });
}

QString AuthRouter::getName() const {
  return "auth";
}

} // namespace light
