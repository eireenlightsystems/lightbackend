#ifndef PERSON_H
#define PERSON_H

#include "Contragent.h"

namespace light {
class Person : public Contragent
{
public:
  Person() = default;
  Person(const Contragent& other);

  QString getNameFirst() const;
  void setNameFirst(const QString& value);

  QString getNameSecond() const;
  void setNameSecond(const QString& value);

  QString getNameThird() const;
  void setNameThird(const QString& value);

private:
  QString nameFirst;
  QString nameSecond;
  QString nameThird;
};
} // namespace light


#endif // PERSON_H
