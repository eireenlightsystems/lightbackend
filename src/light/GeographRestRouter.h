#ifndef GEOGRAPHRESTROUTER_H
#define GEOGRAPHRESTROUTER_H

#include "typedefs.h"

#include <QHttpServerResponse>

namespace light {

class GeographRestRouter
{
public:
  GeographRestRouter() = default;
  static QHttpServerResponse get(const SessionShared& session, const QHttpServerRequest& req);
};

} // namespace light

#endif // GEOGRAPHRESTROUTER_H
