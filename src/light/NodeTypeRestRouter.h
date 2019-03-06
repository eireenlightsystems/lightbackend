#ifndef NODETYPERESTROUTER_H
#define NODETYPERESTROUTER_H

#include "typedefs.h"

#include <QHttpServerResponse>

namespace light {

class NodeTypeRestRouter
{
public:
  NodeTypeRestRouter() = default;
  static QHttpServerResponse get(const SessionShared& session, const QHttpServerRequest& req);
};

} // namespace light

#endif // NODETYPERESTROUTER_H
