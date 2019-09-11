#include "Roleright.h"

namespace light {

ID Roleright::getId() const {
  return id;
}

void Roleright::setId(const ID& value) {
  id = value;
}

ID Roleright::getComponentId() const {
  return componentId;
}

void Roleright::setComponentId(const ID& value) {
  componentId = value;
}

ID Roleright::getRoleId() const {
  return roleId;
}

void Roleright::setRoleId(const ID& value) {
  roleId = value;
}

QString Roleright::getComponentCode() const {
  return componentCode;
}

void Roleright::setComponentCode(const QString& value) {
  componentCode = value;
}

QString Roleright::getComponentName() const {
  return componentName;
}

void Roleright::setComponentName(const QString& value) {
  componentName = value;
}

QString Roleright::getComponentComments() const {
  return componentComments;
}

void Roleright::setComponentComments(const QString& value) {
  componentComments = value;
}

QString Roleright::getRoleName() const {
  return roleName;
}

void Roleright::setRoleName(const QString& value) {
  roleName = value;
}

QString Roleright::getRights() const {
  return rights;
}

void Roleright::setRights(const QString& value) {
  rights = value;
}

} // namespace light
