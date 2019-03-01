#include "Contract.h"

namespace light {

ID Contract::getId() const {
  return id;
}

void Contract::setId(const ID& value) {
  id = value;
}

QString Contract::getCode() const {
  return code;
}

void Contract::setCode(const QString& value) {
  code = value;
}

QString Contract::getName() const {
  return name;
}

void Contract::setName(const QString& value) {
  name = value;
}

} // namespace light
