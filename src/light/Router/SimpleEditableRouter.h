#ifndef SIMPLEEDITABLEROUTER_H
#define SIMPLEEDITABLEROUTER_H

#include "TemplateRouter.h"

namespace light {

template <typename T>
class SimpleEditableRouter : public TemplateRouter<T>
{
  constexpr static bool isEditable = true;
public:
  SimpleEditableRouter() = default;
  ~SimpleEditableRouter() override = default;

  QHttpServerResponse post(const SessionShared& session, const QHttpServerRequest& req) const {
    FromJsonConverter<InsertPatameter> converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto parameters = converter.getParameters();

    Controller<Object, PostgresqlGateway::PostgresCrud> controller;
    controller.setSession(session);
    controller.ins(parameters);
    return QHttpServerResponse(QHttpServerResponse::StatusCode::Ok);
  }
  QHttpServerResponse patch(const SessionShared& session, const QHttpServerRequest& req) const;
  QHttpServerResponse del(const SessionShared& session, const QHttpServerRequest& req) const;
  QHttpServerResponse delById(const SessionShared& session, ID id) const;

};

} // namespace light

#endif // SIMPLEEDITABLEROUTER_H
