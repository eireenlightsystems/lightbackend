#ifndef NODERESTROUTER_H
#define NODERESTROUTER_H

#include "AbstractRestRouter.h"

namespace light {
class NodeRestRouter : public AbstractRestRouter
{
public:
  NodeRestRouter() = default;
  QList<ApiItem> getApiItems() override;
  static QHttpServerResponse get(const SessionShared& session, const QHttpServerRequest& req);
  static QHttpServerResponse post(const SessionShared& session, const QHttpServerRequest& req);
  static QHttpServerResponse patch(const SessionShared& session, const QHttpServerRequest& req);
};
} // namespace light

#endif // NODERESTROUTER_H
