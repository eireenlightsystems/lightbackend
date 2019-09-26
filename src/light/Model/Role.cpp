#include "Role.h"
#include "User.h"

namespace light {

ID Role::getId() const {
  return id;
}

void Role::setId(const ID& value) {
  id = value;
}

ID Role::getContragentId() const {
  return contragentId;
}

void Role::setContragentId(const ID& value) {
  contragentId = value;
}

QString Role::getContragentCode() const {
  return contragentCode;
}

void Role::setContragentCode(const QString& value) {
  contragentCode = value;
}

QString Role::getContragentName() const {
  return contragentName;
}

void Role::setContragentName(const QString& value) {
  contragentName = value;
}

QString Role::getContragentInn() const {
  return contragentInn;
}

void Role::setContragentInn(const QString& value) {
  contragentInn = value;
}

QString Role::getContragentAdres() const {
  return contragentAdres;
}

void Role::setContragentAdres(const QString& value) {
  contragentAdres = value;
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

UserSharedList Role::getUsers() const
{
    return users;
}

void Role::setUsers(const UserSharedList &value)
{
  users = value;
}

void Role::removeUser(ID userId)
{
  auto it = std::remove_if(users.begin(), users.end(), [userId](const UserShared& user) {
    return user->getId() == userId;
  });
  if (it != users.end()) {
    users.erase(it);
  }
}

void Role::addUser(const UserShared &user)
{
  users << user;
}

} // namespace light
