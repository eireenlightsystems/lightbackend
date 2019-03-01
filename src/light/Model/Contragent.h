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

  QString getName() const;
  void setName(const QString& value);

  QString getCode() const;
  void setCode(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
};
} // namespace light

#endif // CONTRAGENT_H
