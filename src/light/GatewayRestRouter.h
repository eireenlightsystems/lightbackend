#ifndef GATEWAYRESTROUTER_H
#define GATEWAYRESTROUTER_H

#include "typedefs.h"

#include <QHttpServerResponse>

namespace light {

class GatewayRestRouter
{
public:
  GatewayRestRouter() = default;
  static QHttpServerResponse get(const SessionShared& session, const QHttpServerRequest& req);
  static QHttpServerResponse post(const SessionShared& session, const QHttpServerRequest& req);
  static QHttpServerResponse patch(const SessionShared& session, const QHttpServerRequest& req);
  static QHttpServerResponse del(const SessionShared& session, const QHttpServerRequest& req);

  static QHttpServerResponse getOwner(const SessionShared& session, const QHttpServerRequest& req);
  static QHttpServerResponse getTypes(const SessionShared& session, const QHttpServerRequest& req);
};

} // namespace light

#endif // GATEWAYRESTROUTER_H
