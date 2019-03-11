#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "typedefs.h"
#include <functional>

namespace light {

class SessionOwner
{
public:
  SessionShared getSession() const;
  void setSession(const SessionShared& value);

private:
  SessionShared session;
};

template <typename T, template <typename> class Crud>
class Inserter : public SessionOwner
{
public:
  template <typename... Args>
  void ins(Args&&... args);
};

template <typename T, template <typename> class Crud>
class Updater : public SessionOwner
{
public:
  template <typename... Args>
  void upd(Args&&... args);
};

template <typename T, template <typename> class Crud>
class Deleter : public SessionOwner
{
public:
  void del(const QList<QSharedPointer<T>>& objects) {
    Crud<T> crud;
    crud.setSession(getSession());
    crud.del(objects);
  }
};

template <typename T, template <typename> class Crud>
class Controller
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  Controller() = default;
  ~Controller() = default;

  template <typename... Args>
  SharedList sel(Args&&...) const;

  template <typename... Args>
  void ins(Args&&... args);
  template <typename... Args>
  void upd(Args&&... args);
  void del(const IDList& ids) const;

  SessionShared getSession() const;
  void setSession(const SessionShared& value);

protected:
  Crud<T> createCrud() const;

private:
  SessionShared session;
};

template <typename T, template <typename> class Crud>
template <typename... Args>
typename Controller<T, Crud>::SharedList Controller<T, Crud>::sel(Args&&... args) const {
  auto crud = createCrud();
  return crud.sel(std::forward<Args>(args)...);
}

template <typename T, template <typename> class Crud>
template <typename... Args>
void Controller<T, Crud>::ins(Args&&... args) {
  Inserter<T, Crud> inserter;
  inserter.setSession(session);
  inserter.ins(std::forward<Args>(args)...);
}

template <typename T, template <typename> class Crud>
template <typename... Args>
void Controller<T, Crud>::upd(Args&&... args) {
  Updater<T, Crud> updater;
  updater.setSession(session);
  updater.upd(std::forward<Args>(args)...);
}

template <typename T, template <typename> class Crud>
void Controller<T, Crud>::del(const IDList& ids) const {
  auto crud = createCrud();
  auto objects = crud.sel(qAsConst(ids));
  Deleter<T, Crud> deleter;
  deleter.setSession(session);
  deleter.del(qAsConst(objects));
}

template <typename T, template <typename> class Crud>
Crud<T> Controller<T, Crud>::createCrud() const {
  Crud<T> crud;
  crud.setSession(session);
  return crud;
}

template <typename T, template <typename> class Crud>
SessionShared Controller<T, Crud>::getSession() const {
  return session;
}

template <typename T, template <typename> class Crud>
void Controller<T, Crud>::setSession(const SessionShared& value) {
  session = value;
}

} // namespace light

#endif // CONTROLLER_H
