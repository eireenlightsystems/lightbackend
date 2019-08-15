#include "User.h"

namespace light {

ID User::getId() const {
  return id;
}

void User::setId(const ID& value) {
  id = value;
}

QString User::getLogin() const {
  return login;
}

void User::setLogin(const QString& value) {
  login = value;
}

QString User::getPassword() const {
  return password;
}

void User::setPassword(const QString& value) {
  password = value;
}

ID User::getContragentId() const {
  return contragentId;
}

void User::setContragentId(const ID& value) {
  contragentId = value;
}

QString User::getContragentCode() const {
  return contragentCode;
}

void User::setContragentCode(const QString& value) {
  contragentCode = value;
}

QString User::getContragentName() const {
  return contragentName;
}

void User::setContragentName(const QString& value) {
  contragentName = value;
}

QString User::getContragentInn() const {
  return contragentInn;
}

void User::setContragentInn(const QString& value) {
  contragentInn = value;
}

QString User::getContragentAdres() const {
  return contragentAdres;
}

void User::setContragentAdres(const QString& value) {
  contragentAdres = value;
}

QString User::getComments() const {
  return comments;
}

void User::setComments(const QString& value) {
  comments = value;
}

} // namespace light
