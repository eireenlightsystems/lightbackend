#ifndef GEOGRAPHFIASCONTROLLER_H
#define GEOGRAPHFIASCONTROLLER_H

#include "Controller.h"
#include "GeographFias.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<GeographFias, Crud> : public EditableController<GeographFias, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<GeographFias, Crud>::ins(const QList<QVariantHash>& params) {
  GeographFiasSharedList newGeographFiases;
  for (const auto& param : params){
    auto newGeographFias = GeographFiasShared::create();

    if (param.contains("postalCode")) {
      QString postalCode = param.value("postalCode").toString();
      newGeographFias->setPostalCode(postalCode);
    }

    if (param.contains("okato")) {
      QString okato = param.value("okato").toString();
      newGeographFias->setOkato(okato);
    }

    if (param.contains("fiasLevel")) {
      ID fiasLevel = param.value("fiasLevel").value<ID>();
      newGeographFias->setFiasLevel(fiasLevel);
    }

    if (param.contains("regionFiasId")) {
      QString regionFiasId = param.value("regionFiasId").toString();
      newGeographFias->setRegionFiasId(regionFiasId);
    }

    if (param.contains("regionWithType")) {
      QString regionWithType = param.value("regionWithType").toString();
      newGeographFias->setRegionWithType(regionWithType);
    }

    if (param.contains("areaFiasId")) {
      QString areaFiasId = param.value("areaFiasId").toString();
      newGeographFias->setAreaFiasId(areaFiasId);
    }

    if (param.contains("areaWithType")) {
      QString areaWithType = param.value("areaWithType").toString();
      newGeographFias->setAreaWithType(areaWithType);
    }

    if (param.contains("cityFiasId")) {
      QString cityFiasId = param.value("cityFiasId").toString();
      newGeographFias->setCityFiasId(cityFiasId);
    }

    if (param.contains("cityWithType")) {
      QString cityWithType = param.value("cityWithType").toString();
      newGeographFias->setCityWithType(cityWithType);
    }

    if (param.contains("cityDistrictFiasId")) {
      QString cityDistrictFiasId = param.value("cityDistrictFiasId").toString();
      newGeographFias->setCityDistrictFiasId(cityDistrictFiasId);
    }

    if (param.contains("cityDistrictWithType")) {
      QString cityDistrictWithType = param.value("cityDistrictWithType").toString();
      newGeographFias->setCityDistrictWithType(cityDistrictWithType);
    }

    if (param.contains("settlementFiasId")) {
      QString settlementFiasId = param.value("settlementFiasId").toString();
      newGeographFias->setSettlementFiasId(settlementFiasId);
    }

    if (param.contains("settlementWithType")) {
      QString settlementWithType = param.value("settlementWithType").toString();
      newGeographFias->setSettlementWithType(settlementWithType);
    }

    if (param.contains("streetFiasId")) {
      QString streetFiasId = param.value("streetFiasId").toString();
      newGeographFias->setStreetFiasId(streetFiasId);
    }

    if (param.contains("streetWithType")) {
      QString streetWithType = param.value("streetWithType").toString();
      newGeographFias->setStreetWithType(streetWithType);
    }

    if (param.contains("houseFiasId")) {
      QString houseFiasId = param.value("houseFiasId").toString();
      newGeographFias->setHouseFiasId(houseFiasId);
    }

    if (param.contains("houseWithType")) {
      QString houseWithType = param.value("houseWithType").toString();
      newGeographFias->setHouseWithType(houseWithType);
    }

    newGeographFiases << newGeographFias;
  }

  Crud<GeographFias> geographFiasCrud;
  geographFiasCrud.setSession(this->getSession());
  geographFiasCrud.save(newGeographFiases);
  IDList result;
  std::transform(newGeographFiases.begin(), newGeographFiases.end(), std::back_inserter(result), [](const GeographFiasShared& geographFias) {
    return geographFias->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<GeographFias, Crud>::upd(const QList<QVariantHash>& params) {
  Q_UNUSED(params)
}

template <template <typename> class Crud>
void Controller<GeographFias, Crud>::upd(ID id, const QVariantHash& param) {
  Q_UNUSED(id)
  Q_UNUSED(param)
}

} // namespace light

#endif // GEOGRAPHFIASCONTROLLER_H
