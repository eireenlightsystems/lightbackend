#include "PostgresCrudGeographFias.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> geographFiasFields {
    {"id", "id", true},
    {"postal_code", "postal_code", false},
    {"okato", "okato", false},
    {"fias_level", "fias_level", false},
    {"region_fias_id", "region_fias_id", false},
    {"region_with_type", "region_with_type", false},
    {"area_fias_id", "area_fias_id", false},
    {"area_with_type", "area_with_type", false},
    {"city_fias_id", "city_fias_id", false},
    {"city_with_type", "city_with_type", false},
    {"city_district_fias_id", "city_district_fias_id", false},
    {"city_district_with_type", "city_district_with_type", false},
    {"settlement_fias_id", "settlement_fias_id", false},
    {"settlement_with_type", "settlement_with_type", false},
    {"street_fias_id", "street_fias_id", false},
    {"street_with_type", "street_with_type", false},
    {"house_fias_id", "house_fias_id", false},
    {"house_with_type", "house_with_type", false},
    {"geo_lat", "geo_lat", false},
    {"geo_lon", "geo_lon", false},
    };

PostgresCrud<GeographFias>::PostgresCrud() {
  setFields(geographFiasFields);
  setInsertSql("select geograph_pkg_i.save_dadata(:postal_code, :okato, :fias_level, :region_fias_id, :region_with_type, :area_fias_id, :area_with_type, :city_fias_id, :city_with_type, :city_district_fias_id, :city_district_with_type, :settlement_fias_id, :settlement_with_type, :street_fias_id, :street_with_type, :house_fias_id, :house_with_type, :geo_lat, :geo_lon)");
}

Reader<GeographFias>::Shared PostgresCrud<GeographFias>::parse(const QSqlRecord& record) const {
  auto geographFias = GeographFiasShared::create();
  geographFias->setId(record.value(getFieldAlias("id")).value<ID>());
  geographFias->setPostalCode(record.value(getFieldAlias("postal_code")).toString());
  geographFias->setOkato(record.value(getFieldAlias("okato")).toString());
  geographFias->setFiasLevel(record.value(getFieldAlias("fias_level")).value<ID>());
  geographFias->setRegionFiasId(record.value(getFieldAlias("region_fias_id")).toString());
  geographFias->setRegionWithType(record.value(getFieldAlias("region_with_type")).toString());
  geographFias->setAreaFiasId(record.value(getFieldAlias("area_fias_id")).toString());
  geographFias->setAreaWithType(record.value(getFieldAlias("area_with_type")).toString());
  geographFias->setCityFiasId(record.value(getFieldAlias("city_fias_id")).toString());
  geographFias->setCityWithType(record.value(getFieldAlias("city_with_type")).toString());

  geographFias->setCityDistrictFiasId(record.value(getFieldAlias("city_district_fias_id")).toString());
  geographFias->setCityDistrictWithType(record.value(getFieldAlias("city_district_with_type")).toString());
  geographFias->setSettlementFiasId(record.value(getFieldAlias("settlement_fias_id")).toString());
  geographFias->setSettlementWithType(record.value(getFieldAlias("settlement_with_type")).toString());
  geographFias->setStreetFiasId(record.value(getFieldAlias("street_fias_id")).toString());
  geographFias->setStreetWithType(record.value(getFieldAlias("street_with_type")).toString());
  geographFias->setHouseFiasId(record.value(getFieldAlias("house_fias_id")).toString());
  geographFias->setHouseWithType(record.value(getFieldAlias("house_with_type")).toString());

  geographFias->setGeoLat(record.value(getFieldAlias("geo_lat")).toString());
  geographFias->setGeoLon(record.value(getFieldAlias("geo_lon")).toString());

  return geographFias;
}

BindParamsType PostgresCrud<GeographFias>::getInsertParams(const Editor::Shared &geographFias) const
{
  return BindParamsType{
      {":postal_code", geographFias->getPostalCode()},
      {":okato", geographFias->getOkato()},
      {":fias_level", geographFias->getFiasLevel()},
      {":region_fias_id", geographFias->getRegionFiasId()},
      {":region_with_type", geographFias->getRegionWithType()},
      {":area_fias_id", geographFias->getAreaFiasId()},
      {":area_with_type", geographFias->getAreaWithType()},
      {":city_fias_id", geographFias->getCityFiasId()},
      {":city_with_type", geographFias->getCityWithType()},

      {":city_district_fias_id", geographFias->getCityDistrictFiasId()},
      {":city_district_with_type", geographFias->getCityDistrictWithType()},
      {":settlement_fias_id", geographFias->getSettlementFiasId()},
      {":settlement_with_type", geographFias->getSettlementWithType()},
      {":street_fias_id", geographFias->getStreetFiasId()},
      {":street_with_type", geographFias->getStreetWithType()},
      {":house_fias_id", geographFias->getHouseFiasId()},
      {":house_with_type", geographFias->getHouseWithType()},

      {":geo_lat", geographFias->getGeoLat()},
      {":geo_lon", geographFias->getGeoLon()},
  };
}

BindParamsType PostgresCrud<GeographFias>::getUpdateParams(const Editor::Shared &object) const
{
  return BindParamsType();
}

} // namespace PostgresqlGateway
} // namespace light
