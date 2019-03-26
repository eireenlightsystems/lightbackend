#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "LigthBackend.h"

#include <QHttpServer>
#include <QObject>

namespace light {
class HttpServerWrapper : public QObject
{
  Q_OBJECT
public:
  explicit HttpServerWrapper(QObject* parent = nullptr);
  ~HttpServerWrapper() override = default;

  static QSharedPointer<HttpServerWrapper> singleton();
  static QJsonDocument errorStringToJson(const QString& error);
  static QJsonDocument errorStringToJson(const char* error);

  void createRoutes();
  void listen(const QHostAddress& address, quint16 port);

  QSharedPointer<LigthBackend> getLightBackend() const;
  void setLightBackend(const QSharedPointer<LigthBackend>& value);

  bool isLoggedIn() const;

private:
  void createCommandsRoutes();
  void createNodeRoutes();
  void createGatewayRouters();
  void createFixtureRouters();
  void createFixtureGroupRouters();
  void createDictionary();

private:
  QHttpServer httpServer;
  QSharedPointer<LigthBackend> lightBackendShared;
};

} // namespace light

#endif // HTTPSERVER_H
