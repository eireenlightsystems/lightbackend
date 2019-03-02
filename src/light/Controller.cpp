#include "Controller.h"

#include "Session.h"

namespace light {

template <typename T, template<typename> class Crud>
template <typename... Args>
void Controller<T, Crud>::ins(Args... args) {
}

template <typename T, template<typename> class Crud>
void Controller<T, Crud>::upd() {
}

template <typename T, template<typename> class Crud>
void Controller<T, Crud>::del(const IDList& ids) {
  auto crud = createCrud();
  auto objects = crud.sel(ids);
  checkBeforeDel(objects);
  baseDel(objects);
}

} // namespace light
