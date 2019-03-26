#ifndef HELPERS_H
#define HELPERS_H

#include "typedefs.h"

namespace light {
namespace helpers {

template <typename T, template <typename> class Container>
void removeById(Container<T>& container, ID id) {
  auto it = std::remove_if(
      container.begin(), container.end(), [id](const typename Container<T>::value_type& object) { return object->getId() == id; });
  if (it != container.end()) {
    container.erase(it);
  }
}

template <typename T, template <typename> class Container>
void removeByIds(Container<T>& container, const IDList& ids) {
  for (auto id : ids) {
    removeById(container, id);
  }
}

} // namespace helpers
} // namespace light

#endif // HELPERS_H
