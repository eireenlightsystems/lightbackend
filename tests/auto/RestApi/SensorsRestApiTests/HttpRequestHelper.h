#ifndef HTTPREQUESTHELPER_H
#define HTTPREQUESTHELPER_H

#include <QJsonArray>
#include <QNetworkAccessManager>

class HttpRequestHelper : public QObject
{
  Q_OBJECT
public:
  explicit HttpRequestHelper(QObject* parent = nullptr);
  QJsonArray get(const QList<QPair<QString, QString>>& queriItems = QList<QPair<QString, QString>>());
  QJsonObject getById(qulonglong id);

  qulonglong post(const QJsonObject& object);
  QList<qulonglong> post(const QJsonArray& array);

  void patch(const QJsonObject& object);

  void del(qulonglong id);
  void del(QList<qulonglong> ids);

  QString getRouterPrefix() const;
  void setRouterPrefix(const QString& value);

  QString getRoute() const;
  void setRoute(const QString& value);

  int getLastStatusCode() const;

private:
  QNetworkAccessManager manager;
  QString routerPrefix;
  QString route;
  int lastStatusCode{0};
};

#endif // HTTPREQUESTHELPER_H
