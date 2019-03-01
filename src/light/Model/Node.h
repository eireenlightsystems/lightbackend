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
  void setCoordinate(const QGeoCoordinate& value);
  void setCoordinate(double latitude, double longitude);

  double getPrice() const;
  void setPrice(double value);

  QString getComment() const;
  void setComment(const QString& value);

  ContragentShared getOwner() const;
  void setOwner(const ContragentShared& value);

  EquipmentTypeShared getEquipmentType() const;
  void setEquipmentType(const EquipmentTypeShared& value);

  GeographShared getGeograph() const;
  void setGeograph(const GeographShared& value);

  ContractShared getContract() const;
  void setContract(const ContractShared& value);

private:
  ID id{0};
  QGeoCoordinate coordinate;
  double price{0.0};
  QString comment;
  ContragentShared owner;
  EquipmentTypeShared equipmentType;
  GeographShared geograph;
  ContractShared contract;
};
} // namespace light

#endif // NODE_H
