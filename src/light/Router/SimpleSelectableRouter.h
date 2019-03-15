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

  virtual QHttpServerResponse get(ID id) {
    auto controller = createController();
    auto objects = controller.sel(IDList{id});

    ToJsonConverter<T> converter;
    converter.convert(objects);
    if (!converter.getIdValid()) {
      throw InternalServerErrorException(converter.getErrorText());
    }
    QJsonDocument jsonDocument(converter.getJsonDocument());
    return QHttpServerResponse("text/json", jsonDocument.toJson());
  }

  virtual QHttpServerResponse get(const QHttpServerRequest& req) {
    auto queryItems = parseUrlQuery(req.query());
    auto controller = createController();
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
  Controller<T, CRUD> createController() const {
    Controller<T, CRUD> controller;
    controller.setSession(getSession());
    return controller;
  }

  virtual QVariantHash parseUrlQuery(const QUrlQuery& urlQuery) const {
    QVariantHash params;
    for (const auto& item : urlQuery.queryItems()) {
      QVariant id = item.second.isEmpty() ? QVariant() : QVariant(item.second.toULongLong());
      params[item.first] = id;
    }
    return params;
  }
}; // namespace light
} // namespace light

#endif // SIMPLESELECTABLEROUTER_H
