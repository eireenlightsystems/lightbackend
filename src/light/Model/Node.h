#ifndef NODE_H
#define NODE_H

#include "Contract.h"
#include "Contragent.h"
#include "Equipment.h"

#include <QGeoCoordinate>

namespace light {

class NodeContract : public Contract
{
public:
  NodeContract() = default;
  explicit NodeContract(const Contract& other) : Contract(other) {
  }
};

class NodeOwner : public Contragent
{
public:
  NodeOwner() = default;
  explicit NodeOwner(const Contragent& other) : Contragent(other) {
  }
};

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
  ID getGeographId() const;
  QString getGeographFullName() const;

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
