#ifndef NODE_H
#define NODE_H

#include "Equipment.h"

#include <QGeoCoordinate>

namespace light {
class Node : public Equipment
{
public:
  Node() = default;

  QGeoCoordinate getCoordinate() const;
  double getLatitude() const;
  double getLongitude() const;
  void setCoordinate(const QGeoCoordinate& value);
  void setCoordinate(double latitude, double longitude);

  NodeTypeShared getNodeType() const;
  ID getNodeTypeId() const;
  void setNodeType(const NodeTypeShared& value);

  GeographShared getGeograph() const override;
  void setGeograph(const GeographShared& value);

  FixtureSharedList getFixtures() const;
  void setFixtures(const FixtureSharedList& value);
  void addFixtures(const FixtureSharedList& value);
  void removeFixtures(const IDList& ids);

  GatewaySharedList getGateways() const;
  void setGateways(const GatewaySharedList& value);
  void addGateways(const GatewaySharedList& value);
  void removeGateways(const IDList& ids);

  SensorSharedList getSensors() const;
  void setSensors(const SensorSharedList& value);
  void addSensors(const SensorSharedList& value);
  void removeSensors(const IDList& ids);

  int getNumberInGroup() const;
  void setNumberInGroup(int value);

private:
  QGeoCoordinate coordinate;
  NodeTypeShared nodeType;
  GeographShared geograph;
  FixtureSharedList fixtures;
  GatewaySharedList gateways;
  SensorSharedList sensors;
  int numberInGroup;
};
} // namespace light

#endif // NODE_H
