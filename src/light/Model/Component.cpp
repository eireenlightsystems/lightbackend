#include "Component.h"

namespace light {

ID Component::getId() const {
  return id;
}

void Component::setId(const ID& value) {
  id = value;
}

QString Component::getCode() const {
  return code;
}

void Component::setCode(const QString& value) {
  code = value;
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

QString Component::getRights() const {
  return rights;
}

void Component::setRights(const QString& value) {
  rights = value;
}
} // namespace light

