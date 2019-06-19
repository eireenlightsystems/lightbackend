#ifndef SENSORTYPECONTROLLER_H
#define SENSORTYPECONTROLLER_H

#include "Controller.h"
#include "SensorType.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<SensorType, Crud> : public EditableController<SensorType, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<SensorType, Crud>::ins(const QList<QVariantHash>& params) {
 SensorTypeSharedList newSensorTypes;
  for (const auto& param : params){
    auto newSensorType = SensorTypeShared::create();

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newSensorType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newSensorType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      newSensorType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      newSensorType->setComment(comment);
    }

    if (param.contains("detectionRange")) {
      double detectionRange = param.value("detectionRange").toDouble();
      newSensorType->setDetectionRange(detectionRange);
    }

    newSensorTypes << newSensorType;
  }

  Crud<SensorType> nodeTypeCrud;
  nodeTypeCrud.setSession(this->getSession());
  nodeTypeCrud.save(newSensorTypes);
  IDList result;
  std::transform(newSensorTypes.begin(), newSensorTypes.end(), std::back_inserter(result), [](const SensorTypeShared& sensorType) {
    return sensorType->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<SensorType, Crud>::upd(const QList<QVariantHash>& params) {
  SensorTypeSharedList sensorTypes;
  Crud<SensorType> sensorTypeCrud;
  sensorTypeCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID sensorTypeId = param.value("id").value<ID>();
    auto sensorType = sensorTypeCrud.selById(sensorTypeId);

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      sensorType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      sensorType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      sensorType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      sensorType->setComment(comment);
    }

    if (param.contains("detectionRange")) {
      double detectionRange = param.value("detectionRange").toDouble();
      sensorType->setDetectionRange(detectionRange);
    }

    sensorTypes << sensorType;
  }

  sensorTypeCrud.save(sensorTypes);
}

template <template <typename> class Crud>
void Controller<SensorType, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // SENSORTYPECONTROLLER_H
