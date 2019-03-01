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

  template <typename RouteFunction, typename... Args>
  static QHttpServerResponse baseRouteFunction(RouteFunction routeFunction, Args&&... args);

  bool isLoggedIn() const;

protected:
  template<typename Converter, typename BackendGetter>
  QHttpServerResponse getFixturesCommandsBase(BackendGetter);

private:
  void createCommandsRoutes();
  void createLightLevelRoutes();
  void createLightSpeedRoutes();
  void createNodeRoutes();

private:
  QHttpServer httpServer;
  QSharedPointer<LigthBackend> lightBackendShared;
};

} // namespace light

#endif // HTTPSERVER_H
