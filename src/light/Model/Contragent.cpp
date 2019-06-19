#include "Contragent.h"
#include "Geograph.h"

namespace light {

ID Contragent::getId() const {
  return id;
}

void Contragent::setId(const ID& value) {
  id = value;
}

QString Contragent::getCode() const {
  return code;
}

void Contragent::setCode(const QString& value) {
  code = value;
}

QString Contragent::getName() const {
  return name;
}

void Contragent::setName(const QString& value) {
  name = value;
}


//GeographShared Contragent::getGeograph() const {
//  return geograph;
//}

//ID Contragent::getGeographId() const {
//  if (geograph)
//    return geograph->getId();

//  return 0;
//}

//void Contragent::setGeograph(const GeographShared& value) {
//  geograph = value;
//}

ID Contragent::getGeographId() const {
  return geographId;
}

void Contragent::setGeographId(const ID& value) {
  geographId = value;
}

QString Contragent::getInn() const {
  return inn;
}

void Contragent::setInn(const QString& value) {
  inn = value;
}

QString Contragent::getComments() const {
  return comments;
}

void Contragent::setComments(const QString& value) {
  comments = value;
}

} // namespace light
