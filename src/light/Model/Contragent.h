#ifndef CONTRAGENT_H
#define CONTRAGENT_H

#include "typedefs.h"

namespace light {
class Contragent
{
public:
  Contragent() = default;
  Contragent(const Contragent & other);

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  QString getInn() const;
  void setInn(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

  GeographShared getGeograph() const;
  void setGeograph(const GeographShared &value);
  ID getGeographId() const;
  QString getGeographCode() const;

private:
  ID id{0};
  QString code;
  QString name;
  GeographShared geograph;
  QString inn;
  QString comments;
};
} // namespace light

#endif // CONTRAGENT_H
