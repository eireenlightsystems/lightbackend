#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "typedefs.h"

namespace light {

template <typename T, template <typename> class Crud>
class Controller
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  Controller() = default;
  ~Controller() = default;

  template <typename... Ts>
  SharedList sel(Ts...) const;

  template <typename... Ts>
  void ins(Ts... args);
  void upd();
  void del(const IDList& ids);

  SessionShared getSession() const;
  void setSession(const SessionShared& value);

protected:
  void checkBeforeDel(const SharedList& objects) const;
  void baseDel(const SharedList& objects) const;
  Crud<T> createCrud() const;

private:
  SessionShared session;
};

template <typename T, template <typename> class Crud>
template <typename... Args>
typename Controller<T, Crud>::SharedList Controller<T, Crud>::sel(Args... args) const {
  auto crud = createCrud();
  return crud.sel(std::forward<Args>(args)...);
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
