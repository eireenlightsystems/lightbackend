#ifndef REPORTCOUNTFIXTURE_H
#define REPORTCOUNTFIXTURE_H

#include "typedefs.h"

namespace light {
class ReportCountFixture
{
public:
  ReportCountFixture() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getRegion() const;
  void setRegion(const QString& value);

  QString getArea() const;
  void setArea(const QString& value);

  QString getCity() const;
  void setCity(const QString& value);

  QString getCityDistrict() const;
  void setCityDistrict(const QString& value);

  QString getSettlement() const;
  void setSettlement(const QString& value);

  QString getStreet() const;
  void setStreet(const QString& value);

  QString getHouse() const;
  void setHouse(const QString& value);

  QString getCodeContract() const;
  void setCodeContract(const QString& value);

  QString getCodeFixtureType() const;
  void setCodeFixtureType(const QString& value);

  QString getCodeInstaller() const;
  void setCodeInstaller(const QString& value);

  QString getCodeSubstation() const;
  void setCodeSubstation(const QString& value);

  QString getCodeHeightType() const;
  void setCodeHeightType(const QString& value);

  QString getCodeOwner() const;
  void setCodeOwner(const QString& value);

  int getCountFixture() const;
  void setCountFixture(int value);

private:
  ID id{0};
  QString region;
  QString area;
  QString city;
  QString cityDistrict;
  QString settlement;
  QString street;
  QString house;
  QString codeContract;
  QString codeFixtureType;
  QString codeInstaller;
  QString codeSubstation;
  QString codeHeightType;
  QString codeOwner;
  int countFixture;
};
} // namespace light

#endif // REPORTCOUNTFIXTURE_H
