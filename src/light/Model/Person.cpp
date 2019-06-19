#include "Person.h"

namespace light {


QString Person::getNameFirst() const {
  return nameFirst;
}

void Person::setNameFirst(const QString& value) {
  nameFirst = value;
}

QString Person::getNameSecond() const {
  return nameSecond;
}

void Person::setNameSecond(const QString& value) {
  nameSecond = value;
}

QString Person::getNameThird() const {
  return nameThird;
}

void Person::setNameThird(const QString& value) {
  nameThird = value;
}

} // namespace light
