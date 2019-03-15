#ifndef SIMPLESELECTABLEROUTER_H
#define SIMPLESELECTABLEROUTER_H

#include "Controller.h"
#include "GatewayTypeDef.h"
#include "InternalServerErrorException.h"
#include "SessionOwner.h"
#include "ToJsonConverter.h"

#include <QHttpServerRequest>
#include <QHttpServerResponse>

namespace light {

using SelectFilters = QVariantHash;

template <typename T>
class SimpleSelectableRouter : public SessionOwner
{
public:
  constexpr static bool isEditable = false;
  constexpr static bool isList = false;

  SimpleSelectableRouter() = default;
  ~SimpleSelectableRouter() override = default;

  QHttpServerResponse get(ID id) {
    Controller<T, CRUD> controller;
    controller.setSession(getSession());
    auto objects = controller.sel(IDList{id});

    ToJsonConverter<T> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

  QHttpServerResponse get(const QHttpServerRequest& req) {
    auto queryItems = parseUrlQuery(req.query());
    Controller<T, CRUD> controller;
    controller.setSession(getSession());
    auto objects = controller.sel(queryItems);

    ToJsonConverter<T> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

protected:
  virtual QVariantHash parseUrlQuery(const QUrlQuery& urlQuery) const {
    Q_UNUSED(urlQuery)
    return QVariantHash();
  }
};
} // namespace light

#endif // SIMPLESELECTABLEROUTER_H
