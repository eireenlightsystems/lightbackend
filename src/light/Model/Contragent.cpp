#include "Contragent.h"
#include "Geograph.h"

namespace light {

Contragent::Contragent(const Contragent &other)
  : id(other.id)
  , code(other.code)
  , name(other.name)
  , geograph(other.geograph)
  , inn(other.inn)
  , comments(other.comments)
{

}

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


GeographShared Contragent::getGeograph() const {
  return geograph;
}

ID Contragent::getGeographId() const {
  if (geograph)
    return geograph->getId();

  return 0;
}

QString Contragent::getGeographCode() const
{
  if (geograph)
    return geograph->getCode();

  return QString();
}

QString Contragent::getGeographName() const
{
  if (geograph)
    return geograph->getName();

  return QString();
}

QString Contragent::getGeographFullName() const
{
  if (geograph)
    return geograph->getFullName();

  return QString();
}

void Contragent::setGeograph(const GeographShared& value) {
  geograph = value;
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
