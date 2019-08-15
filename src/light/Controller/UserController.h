#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "Controller.h"
#include "User.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<User, Crud> : public EditableController<User, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<User, Crud>::ins(const QList<QVariantHash>& params) {
  UserSharedList newUsers;
  for (const auto& param : params){
    auto newUser = UserShared::create();

    if (param.contains("contragentId")) {
      ID contragentId = param.value("contragentId").value<ID>();
      newUser->setContragentId(contragentId);
    }

    if (param.contains("login")) {
      QString login = param.value("login").toString();
      newUser->setLogin(login);
    }

    if (param.contains("password")) {
      QString password = param.value("password").toString();
      newUser->setPassword(password);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newUser->setComments(comments);
    }

    newUsers << newUser;
  }

  Crud<User> userCrud;
  userCrud.setSession(this->getSession());
  userCrud.save(newUsers);
  IDList result;
  std::transform(newUsers.begin(), newUsers.end(), std::back_inserter(result), [](const UserShared& user) {
    return user->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<User, Crud>::upd(const QList<QVariantHash>& params) {
  UserSharedList users;
  Crud<User> userCrud;
  userCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID userId = param.value("id").value<ID>();
    auto user = userCrud.selById(userId);

    if (param.contains("contragentId")) {
      ID contragentId = param.value("contragentId").value<ID>();
      user->setContragentId(contragentId);
    }

    if (param.contains("login")) {
      QString login = param.value("login").toString();
      user->setLogin(login);
    }

    if (param.contains("password")) {
      QString password = param.value("password").toString();
      user->setPassword(password);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      user->setComments(comments);
    }

    users << user;
  }

  userCrud.save(users);
}

template <template <typename> class Crud>
void Controller<User, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // USERCONTROLLER_H
