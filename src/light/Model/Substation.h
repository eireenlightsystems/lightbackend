#ifndef SUBSTATION_H
#define SUBSTATION_H

#include "typedefs.h"
#include "Contragent.h"
#include <QString>

namespace light {
class Substation  : public Contragent
{
public:
  Substation() = default;
  Substation(const Contragent &other);

  ID getOrgFormId() const;
  void setOrgFormId(const ID& value);

  QString getOrgFormCode() const;
  void setOrgFormCode(const QString& value);

  double getPower() const;
  void setPower(double value);

private:
  ID orgFormId{0};
  QString orgFormCode;
  double power{0.0};
};
} // namespace light

#endif // SUBSTATION_H
