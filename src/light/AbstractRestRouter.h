#ifndef ABSTRACTRESTROUTER_H
#define ABSTRACTRESTROUTER_H

#include "typedefs.h"

#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QSqlDatabase>
#include <functional>

namespace light {

class AbstractRestRouter
{
public:
  struct ApiItem
  {
    QString route;
    QHttpServerRequest::Method method;
    std::function<QHttpServerResponse(const SessionShared& session, const QHttpServerRequest& req)> callback;
  };
  virtual ~AbstractRestRouter() = 0;
  virtual QList<ApiItem> getApiItems() = 0;
};
} // namespace light

#endif // ABSTRACTRESTROUTER_H
