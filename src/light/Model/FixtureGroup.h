#ifndef FIXTUREGROUP_H
#define FIXTUREGROUP_H

#include "typedefs.h"

#include <QGeoCoordinate>

namespace light {

class FixtureGroup
{
public:
  FixtureGroup() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getName() const;
  void setName(const QString& value);

  ContragentShared getOwner() const;
  ID getOwnerId() const;
  void setOwner(const ContragentShared& value);

  GeographShared getGeograph() const;
  ID getGeographId() const;
  void setGeograph(const GeographShared& value);

  FixtureGroupTypeShared getType() const;
  ID getTypeId() const;
  void setType(const FixtureGroupTypeShared& value);

  QGeoCoordinate getCoordinate() const;
  double getLatitude() const;
  double getLongitude() const;
  void setCoordinate(const QGeoCoordinate& value);
  void setCoordinate(double latitude, double longitude);

private:
  ID id{0};
  QString name;
  ContragentShared owner;
  GeographShared geograph;
  FixtureGroupTypeShared type;
  QGeoCoordinate coordinate;
};

} // namespace light

#endif // FIXTUREGROUP_H
