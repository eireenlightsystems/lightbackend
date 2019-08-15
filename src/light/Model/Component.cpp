#include "Component.h"

namespace light {

ID Component::getId() const {
  return id;
}

void Component::setId(const ID& value) {
  id = value;
}

QString Component::getName() const {
  return name;
}

void Component::setName(const QString& value) {
  name = value;
}

QString Component::getComments() const {
  return comments;
}

void Component::setComments(const QString& value) {
  comments = value;
}

} // namespace light

