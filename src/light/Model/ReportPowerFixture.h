#ifndef REPORTPOWERFIXTURE_H
#define REPORTPOWERFIXTURE_H


#include "typedefs.h"

namespace light {
class ReportPowerFixture
{
public:
  ReportPowerFixture() = default;

  ID getId() const;
  void setId(const ID& value);

  int getYear() const;
  void setYear(int value);

  QString getMonthName() const;
  void setMonthName(const QString& value);

  int getFixtureId() const;
  void setFixtureId(int value);

  double getHours() const;
  void setHours(double value);

  double getKw() const;
  void setKw(double value);

  double getRub() const;
  void setRub(double value);

private:
  ID id{0};
  int year;
  QString monthName;
  int fixtureId;
  double hours;
  double kw;
  double rub;
};
} // namespace light

#endif // REPORTPOWERFIXTURE_H
