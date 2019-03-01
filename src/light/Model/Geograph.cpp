#include "Geograph.h"

namespace light {

ID Geograph::getId() const {
  return id;
}

void Geograph::setId(const ID& value) {
  id = value;
}

QString Geograph::getName() const {
  return name;
}

void Geograph::setName(const QString& value) {
  name = value;
}

QString Geograph::getCode() const {
  return code;
}

void Geograph::setCode(const QString& value) {
  code = value;
}

} // namespace light
