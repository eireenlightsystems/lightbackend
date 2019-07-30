#ifndef GEOGRAPHFIAS_H
#define GEOGRAPHFIAS_H

#include "typedefs.h"

namespace light {
class GeographFias
{
public:
  GeographFias() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getPostalCode() const;
  void setPostalCode(const QString& value);

  QString getOkato() const;
  void setOkato(const QString& value);

  ID getFiasLevel() const;
  void setFiasLevel(const ID& value);

  QString getRegionFiasId() const;
  void setRegionFiasId(const QString& value);

  QString getRegionWithType() const;
  void setRegionWithType(const QString& value);

  QString getAreaFiasId() const;
  void setAreaFiasId(const QString& value);

  QString getAreaWithType() const;
  void setAreaWithType(const QString& value);

  QString getCityFiasId() const;
  void setCityFiasId(const QString& value);

  QString getCityWithType() const;
  void setCityWithType(const QString& value);

  QString getCityDistrictFiasId() const;
  void setCityDistrictFiasId(const QString& value);

  QString getCityDistrictWithType() const;
  void setCityDistrictWithType(const QString& value);

  QString getSettlementFiasId() const;
  void setSettlementFiasId(const QString& value);

  QString getSettlementWithType() const;
  void setSettlementWithType(const QString& value);

  QString getStreetFiasId() const;
  void setStreetFiasId(const QString& value);

  QString getStreetWithType() const;
  void setStreetWithType(const QString& value);

  QString getHouseFiasId() const;
  void setHouseFiasId(const QString& value);

  QString getHouseWithType() const;
  void setHouseWithType(const QString& value);
private:
  ID id{0};
  QString postalCode;
  QString okato;
  ID fiasLevel;
  QString regionFiasId;
  QString regionWithType;
  QString areaFiasId;
  QString areaWithType;
  QString cityFiasId;
  QString cityWithType;
  QString cityDistrictFiasId;
  QString cityDistrictWithType;
  QString settlementFiasId;
  QString settlementWithType;
  QString streetFiasId;
  QString streetWithType;
  QString houseFiasId;
  QString houseWithType;
};
} // namespace light

#endif // GEOGRAPHFIAS_H
