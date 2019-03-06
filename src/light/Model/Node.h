#ifndef NODE_H
#define NODE_H

#include "typedefs.h"

#include <QGeoCoordinate>

namespace light {
class Node
{
public:
  Node() = default;

  ID getId() const;
  void setId(const ID& value);

  QGeoCoordinate getCoordinate() const;
  double getLatitude() const;
  double getLongitude() const;
  void setCoordinate(const QGeoCoordinate& value);
  void setCoordinate(double latitude, double longitude);

  double getPrice() const;
  void setPrice(double value);

  QString getComment() const;
  void setComment(const QString& value);

  ContragentShared getOwner() const;
  ID getOwnerId() const;
  void setOwner(const ContragentShared& value);

  NodeTypeShared getNodeType() const;
  ID getNodeTypeId() const;
  void setNodeType(const NodeTypeShared& value);

  GeographShared getGeograph() const;
  ID getGeographId() const;
  void setGeograph(const GeographShared& value);

  ContractShared getContract() const;
  ID getContractId() const;
  void setContract(const ContractShared& value);

private:
  ID id{0};
  QGeoCoordinate coordinate;
  double price{0.0};
  QString comment;
  ContragentShared owner;
  NodeTypeShared nodeType;
  GeographShared geograph;
  ContractShared contract;
};
} // namespace light

#endif // NODE_H
