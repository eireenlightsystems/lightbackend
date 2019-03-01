#ifndef GEOGRAPH_H
#define GEOGRAPH_H

#include "typedefs.h"

namespace light {
class Geograph
{
public:
  Geograph() = default;

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

#endif // GEOGRAPH_H
