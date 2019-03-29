#include "HttpRequestHelper.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>

HttpRequestHelper::HttpRequestHelper(QObject* parent) : QObject(parent) {
}

QJsonArray HttpRequestHelper::get(const QList<QPair<QString, QString>>& queriItems) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrlQuery query;
  query.setQueryItems(queriItems);
  QUrl url(QString("%1/%2").arg(routerPrefix, route));
  url.setQuery(query);
  QNetworkRequest request(url);
  QNetworkReply* reply = manager.get(request);
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  auto jsonDocument = QJsonDocument::fromJson(reply->readAll());
  reply->deleteLater();
  return jsonDocument.array();
}

QJsonObject HttpRequestHelper::getById(qulonglong id) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrlQuery query;
  QUrl url(QString("%1/%2/%3").arg(routerPrefix, route).arg(id));
  url.setQuery(query);
  QNetworkRequest request(url);
  QNetworkReply* reply = manager.get(request);
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  auto jsonDocument = QJsonDocument::fromJson(reply->readAll());
  reply->deleteLater();
  if (jsonDocument.array().count()) {
    return jsonDocument.array().first().toObject();
  }
  return QJsonObject();
}

qulonglong HttpRequestHelper::post(const QJsonObject& object) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrl url(QString("%1/%2").arg(routerPrefix, route));
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "text/json");
  QJsonDocument jsonDocument(object);
  QNetworkReply* reply = manager.post(request, jsonDocument.toJson());
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  auto id = reply->readAll().toULongLong();
  reply->deleteLater();

  return id;
}

QList<qulonglong> HttpRequestHelper::post(const QJsonArray& array) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrl url(QString("%1/%2").arg(routerPrefix, route));
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "text/json");
  QJsonDocument jsonDocument(array);
  QNetworkReply* reply = manager.post(request, jsonDocument.toJson());
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  QJsonDocument responseJsonDocument = QJsonDocument::fromJson(reply->readAll());
  reply->deleteLater();
  QList<qulonglong> result;
  QJsonArray ids = responseJsonDocument.array();
  for (auto value : ids) {
    result << value.toVariant().toULongLong();
  }
  return result;
}

void HttpRequestHelper::patch(const QJsonObject& object) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrl url(QString("%1/%2").arg(routerPrefix, route));
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "text/json");
  QJsonDocument jsonDocument(object);
  QNetworkReply* reply = manager.sendCustomRequest(request, "PATCH", jsonDocument.toJson());
  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << reply->error() << reply->errorString();
  }
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  reply->deleteLater();
}

void HttpRequestHelper::del(qulonglong id) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrl url(QString("%1/%2/%3").arg(routerPrefix, route).arg(id));
  QNetworkRequest request(url);
  QNetworkReply* reply = manager.deleteResource(request);
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  reply->deleteLater();
}

void HttpRequestHelper::del(QList<qulonglong> ids) {
  QEventLoop eventLoop;
  connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
  QUrl url(QString("%1/%2").arg(routerPrefix, route));
  QNetworkRequest request(url);
  QStringList stringIds;
  std::transform(
      ids.begin(), ids.end(), std::back_inserter(stringIds), [](qulonglong id) { return QString::number(id); });
  QByteArray data;
  data.append("[" + stringIds.join(',') + "]");
  QNetworkReply* reply = manager.sendCustomRequest(request, "DELETE", data);
  eventLoop.exec();

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  lastStatusCode = statusCode.toInt();
  reply->deleteLater();
}

QString HttpRequestHelper::getRouterPrefix() const {
  return routerPrefix;
}

void HttpRequestHelper::setRouterPrefix(const QString& value) {
  routerPrefix = value;
}

QString HttpRequestHelper::getRoute() const {
  return route;
}

void HttpRequestHelper::setRoute(const QString& value) {
  route = value;
}

int HttpRequestHelper::getLastStatusCode() const {
  return lastStatusCode;
}
