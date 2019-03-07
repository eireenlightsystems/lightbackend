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

private:
  QGeoCoordinate coordinate;
  NodeTypeShared nodeType;
  GeographShared geograph;
};
} // namespace light

#endif // NODE_H
