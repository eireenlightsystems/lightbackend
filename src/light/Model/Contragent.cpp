#include "Contragent.h"

namespace light {

ID Contragent::getId() const {
  return id;
}

void Contragent::setId(const ID& value) {
  id = value;
}

QString Contragent::getName() const {
  return name;
}

void Contragent::setName(const QString& value) {
  name = value;
}

QString Contragent::getCode() const {
  return code;
}

void Contragent::setCode(const QString& value) {
  code = value;
}

} // namespace light
