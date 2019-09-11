#include "Substation.h"

namespace light {

Substation::Substation(const Contragent &other) : Contragent (other)
{
}

ID Substation::getOrgFormId() const {
  return orgFormId;
}

void Substation::setOrgFormId(const ID& value) {
  orgFormId = value;
}

void Substation::setOrgFormCode(const QString& value) {
  orgFormCode = value;
}

QString Substation::getOrgFormCode() const {
  return orgFormCode;
}

double Substation::getPower() const {
  return power;
}

void Substation::setPower(double value) {
  power = value;
}

} // namespace light
