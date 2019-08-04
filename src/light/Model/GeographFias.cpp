#include "GeographFias.h"

namespace light {

ID GeographFias::getId() const {
  return id;
}

void GeographFias::setId(const ID& value) {
  id = value;
}

QString GeographFias::getPostalCode() const {
  return postalCode;
}

void GeographFias::setPostalCode(const QString& value) {
  postalCode = value;
}

QString GeographFias::getOkato() const {
  return okato;
}

void GeographFias::setOkato(const QString& value) {
  okato = value;
}

ID GeographFias::getFiasLevel() const {
  return fiasLevel;
}

void GeographFias::setFiasLevel(const ID& value) {
  fiasLevel = value;
}

QString GeographFias::getRegionFiasId() const {
  return regionFiasId;
}

void GeographFias::setRegionFiasId(const QString& value) {
  regionFiasId = value;
}

QString GeographFias::getRegionWithType() const {
  return regionWithType;
}

void GeographFias::setRegionWithType(const QString& value) {
  regionWithType = value;
}

QString GeographFias::getAreaFiasId() const {
  return areaFiasId;
}

void GeographFias::setAreaFiasId(const QString& value) {
  areaFiasId = value;
}

QString GeographFias::getAreaWithType() const {
  return areaWithType;
}

void GeographFias::setAreaWithType(const QString& value) {
  areaWithType = value;
}

QString GeographFias::getCityFiasId() const {
  return cityFiasId;
}

void GeographFias::setCityFiasId(const QString& value) {
  cityFiasId = value;
}

QString GeographFias::getCityWithType() const {
  return cityWithType;
}

void GeographFias::setCityWithType(const QString& value) {
  cityWithType = value;
}

QString GeographFias::getCityDistrictFiasId() const {
  return cityDistrictFiasId;
}

void GeographFias::setCityDistrictFiasId(const QString& value) {
  cityDistrictFiasId = value;
}

QString GeographFias::getCityDistrictWithType() const {
  return cityDistrictWithType;
}

void GeographFias::setCityDistrictWithType(const QString& value) {
  cityDistrictWithType = value;
}

QString GeographFias::getSettlementFiasId() const {
  return settlementFiasId;
}

void GeographFias::setSettlementFiasId(const QString& value) {
  settlementFiasId = value;
}

QString GeographFias::getSettlementWithType() const {
  return settlementWithType;
}

void GeographFias::setSettlementWithType(const QString& value) {
  settlementWithType = value;
}

QString GeographFias::getStreetFiasId() const {
  return streetFiasId;
}

void GeographFias::setStreetFiasId(const QString& value) {
  streetFiasId = value;
}

QString GeographFias::getStreetWithType() const {
  return streetWithType;
}

void GeographFias::setStreetWithType(const QString& value) {
  streetWithType = value;
}

QString GeographFias::getHouseFiasId() const {
  return houseFiasId;
}

void GeographFias::setHouseFiasId(const QString& value) {
  houseFiasId = value;
}

QString GeographFias::getHouseWithType() const {
  return houseWithType;
}

void GeographFias::setHouseWithType(const QString& value) {
  houseWithType = value;
}

QString GeographFias::getGeoLat() const {
  return geoLat;
}

void GeographFias::setGeoLat(const QString& value) {
  geoLat = value;
}

QString GeographFias::getGeoLon() const {
  return geoLon;
}

void GeographFias::setGeoLon(const QString& value) {
  geoLon = value;
}

} // namespace light
