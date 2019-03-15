#ifndef SIMPLEEDITABLELISTROUTER_H
#define SIMPLEEDITABLELISTROUTER_H

#include "SimpleEditableRouter.h"

namespace light {

template <typename T>
class SimpleEditableListRouter : public SimpleEditableRouter<T>
{
public:
  constexpr static bool isList = true;
  SimpleEditableListRouter() = default;
  ~SimpleEditableListRouter() override = default;

  virtual QHttpServerResponse postListItems(const QHttpServerRequest& req, ID listId) {
    JsonToIds converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto ids = converter.getIds();
    auto controller = this->createController();
    controller.addToList(listId, ids);
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  virtual QHttpServerResponse postListItem(ID listId, ID itemId) {
    auto controller = this->createController();
    controller.addToList(listId, {itemId});
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  virtual QHttpServerResponse delListItems(const QHttpServerRequest& req, ID listId) {
    JsonToIds converter;
    converter.convert(req.body());
    if (!converter.getIdValid()) {
      throw BadRequestException(converter.getErrorText());
    }
    auto ids = converter.getIds();
    auto controller = this->createController();
    controller.delFromList(listId, ids);
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }

  virtual QHttpServerResponse delListItem(ID listId, ID itemId) {
    auto controller = this->createController();
    controller.delFromList(listId, {itemId});
    return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
  }
};
} // namespace light

#endif // SIMPLEEDITABLELISTROUTER_H
