#ifndef CONTRAGENT_H
#define CONTRAGENT_H

#include "typedefs.h"

namespace light {
class Contragent
{
public:
  Contragent() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

//  virtual GeographShared getGeograph() const;
//  ID getGeographId() const;
//  void setGeograph(const GeographShared& value);

  ID getGeographId() const;
  void setGeographId(const ID& value);

  QString getInn() const;
  void setInn(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
  ID geographId{0};
//  GeographShared geograph;
  QString inn;
  QString comments;
};
} // namespace light

#endif // CONTRAGENT_H
