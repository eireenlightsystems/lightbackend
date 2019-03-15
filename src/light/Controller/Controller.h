#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SessionOwner.h"
#include <functional>

namespace light {

template <typename T, template <typename> class Crud>
class Inserter : public SessionOwner
{
public:
  template <typename... Args>
  IDList ins(Args&&... args);
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
class DeleterFromList : public SessionOwner
{
public:
  void del(ID listId, const IDList & ids);
};

template <typename T, template <typename> class Crud>
class InserterToList : public SessionOwner
{
public:
  void add(ID listId, const IDList & ids);
};

template <typename T, template <typename> class Crud>
class Controller : public SessionOwner
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  Controller() = default;
  ~Controller() = default;

  virtual SharedList sel(const QList<QVariantHash>& filters) const;
  virtual IDList ins(const QList<QVariantHash>& params) = 0;
  virtual void upd(const QList<QVariantHash>& params) = 0;
  virtual void del(const IDList& ids) const;
  virtual void delFromList(ID listId, const IDList & ids) const;
  virtual void addToList(ID listId, const IDList & ids) const;

protected:
  Crud<T> createCrud() const;
};

template <typename T, template <typename> class Crud>
typename Controller<T, Crud>::SharedList Controller<T, Crud>::sel(const QList<QVariantHash>& filters) const {
  auto crud = createCrud();
  return crud.sel(filters);
}

template <typename T, template <typename> class Crud>
IDList Controller<T, Crud>::ins(const QList<QVariantHash>& params) {
  Inserter<T, Crud> inserter;
  inserter.setSession(session);
  return inserter.ins(std::forward<Args>(args)...);
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
  deleter.setSession(getSession());
  deleter.del(qAsConst(objects));
}

template <typename T, template <typename> class Crud>
void Controller<T, Crud>::delFromList(ID listId, const IDList & ids) const {
  DeleterFromList<T, Crud> deleter;
  deleter.setSession(session);
  deleter.del(listId, ids);
}

template <typename T, template <typename> class Crud>
void Controller<T, Crud>::addToList(ID listId, const IDList & ids) const {
  InserterToList<T, Crud> inserter;
  inserter.setSession(session);
  inserter.add(listId, ids);
}

template <typename T, template <typename> class Crud>
Crud<T> Controller<T, Crud>::createCrud() const {
  Crud<T> crud;
  crud.setSession(session);
  return crud;
}

} // namespace light

#endif // CONTROLLER_H
