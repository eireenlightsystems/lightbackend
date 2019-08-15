#include "Role.h"

namespace light {

ID Role::getId() const {
  return id;
}

void Role::setId(const ID& value) {
  id = value;
}

QString Role::getName() const {
  return name;
}

void Role::setName(const QString& value) {
  name = value;
}

QString Role::getComments() const {
  return comments;
}

void Role::setComments(const QString& value) {
  comments = value;
}

} // namespace light
