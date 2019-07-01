#include "ContractType.h"

namespace light {

ID ContractType::getId() const {
  return id;
}

void ContractType::setId(const ID& value) {
  id = value;
}

QString ContractType::getCode() const {
  return code;
}

void ContractType::setCode(const QString& value) {
  code = value;
}

QString ContractType::getName() const {
  return name;
}

void ContractType::setName(const QString& value) {
  name = value;
}

QString ContractType::getComments() const {
  return comments;
}

void ContractType::setComments(const QString& value) {
  comments = value;
}

} // namespace light


