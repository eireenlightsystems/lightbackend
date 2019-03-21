#include "FixtureCommandRestRouter.h"

namespace light {

QHttpServerResponse RestRouter<FixtureCommand>::get(ID id) {
  Q_UNUSED(id)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

QHttpServerResponse RestRouter<FixtureCommand>::get(const QHttpServerRequest& req) {
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

QHttpServerResponse RestRouter<FixtureCommand>::post(const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

QHttpServerResponse RestRouter<FixtureCommand>::patch(const QHttpServerRequest& req) const {
  Q_UNUSED(req)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

QHttpServerResponse RestRouter<FixtureCommand>::patch(const QHttpServerRequest& req, ID id) const {
  Q_UNUSED(req)
  Q_UNUSED(id)
  return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
}

} // namespace light
