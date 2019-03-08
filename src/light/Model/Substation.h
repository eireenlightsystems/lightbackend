#ifndef SUBSTATION_H
#define SUBSTATION_H

#include "typedefs.h"

#include <QString>

namespace light {
class Substation
{
public:
  Substation() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  double getPower() const;
  void setPower(double value);

private:
  ID id{0};
  QString code;
  QString name;
  double power{0.0};
};
} // namespace light

#endif // SUBSTATION_H
