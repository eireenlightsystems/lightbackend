#include "Roleinclud.h"

namespace light {

ID Roleinclud::getId() const {
  return id;
}

void Roleinclud::setId(const ID& value) {
  id = value;
}

ID Roleinclud::getRoleId() const {
  return roleId;
}

void Roleinclud::setRoleId(const ID& value) {
  roleId = value;
}

ID Roleinclud::getUserId() const {
  return userId;
}

void Roleinclud::setUserId(const ID& value) {
  userId = value;
}

} // namespace light
