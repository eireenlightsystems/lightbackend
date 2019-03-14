#include "Substation.h"

namespace light {

ID Substation::getId() const {
  return id;
}

void Substation::setId(const ID& value) {
  id = value;
}

QString Substation::getCode() const {
  return code;
}

void Substation::setCode(const QString& value) {
  code = value;
}

QString Substation::getName() const {
  return name;
}

void Substation::setName(const QString& value) {
  name = value;
}

double Substation::getPower() const {
  return power;
}

void Substation::setPower(double value) {
  power = value;
}

} // namespace light
