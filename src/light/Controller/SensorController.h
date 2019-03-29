#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include "BadRequestException.h"
#include "Controller.h"
#include "Sensor.h"

#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Controller<Sensor, Crud> : public EditableController<Sensor, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Sensor, Crud>::ins(const QList<QVariantHash>& params) {
  SensorSharedList newSensors;

  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<SensorType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(this->getSession());
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());

  for (const auto& param : params) {
    auto newSensor = SensorShared::create();
    ContractShared contract;
    SensorTypeShared sensorType;
    NodeShared node;
    QString serialNumber;
    QString comment;

    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      contract = contractCrud.selById(contractId);
      if (!contract) {
	throw BadRequestException(QString("contract with id = %1 not found").arg(contractId));
      }
    } else {
      throw BadRequestException("contractId can not be empty");
    }

    if (param.contains("sensorTypeId")) {
      ID sensorTypeId = param.value("sensorTypeId").value<ID>();
      sensorType = gatewayTypeCrud.selById(sensorTypeId);
      if (!sensorType) {
	throw BadRequestException(QString("sensor type with id = %1 not found").arg(sensorTypeId));
      }
    } else {
      throw BadRequestException("sensorTypeId can not be empty");
    }

    {
      ID nodeId = param.contains("nodeId") ? param.value("nodeId").value<ID>() : 1;
      node = nodeCrud.selById(nodeId);
      if (!node) {
	throw BadRequestException(QString("node with id = %1 not found").arg(nodeId));
      }
    }

    if (param.contains("serialNumber")) {
      serialNumber = param.value("serialNumber").toString();
    }

    if (param.contains("comment")) {
      comment = param.value("comment").toString();
    }

    newSensor->setType(sensorType);
    newSensor->setContract(contract);
    newSensor->setNode(node);
    newSensor->setSerialNumber(serialNumber);
    newSensor->setComment(comment);
    newSensors << newSensor;
  }

  Crud<Sensor> sensorCrud;
  sensorCrud.setSession(this->getSession());
  sensorCrud.save(newSensors);
  IDList result;
  std::transform(newSensors.begin(), newSensors.end(), std::back_inserter(result), [](const SensorShared& sensor) {
    return sensor->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Sensor, Crud>::upd(const QList<QVariantHash>& params) {
  SensorSharedList updateSensors;

  Crud<Sensor> sensorCrud;
  sensorCrud.setSession(this->getSession());
  Crud<Contract> contractCrud;
  contractCrud.setSession(this->getSession());
  Crud<SensorType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(this->getSession());
  Crud<Node> nodeCrud;
  nodeCrud.setSession(this->getSession());

  for (const auto& param : params) {
    ID sensorId = param.value("sensorId").value<ID>();
    auto sensor = sensorCrud.selById(sensorId);

    if (param.contains("contractId")) {
      ID contractId = param.value("contractId").value<ID>();
      auto contract = contractCrud.selById(contractId);
      sensor->setContract(contract);
    }

    if (param.contains("sensorTypeId")) {
      ID gatewayTypeId = param.value("sensorTypeId").value<ID>();
      auto gatewayType = gatewayTypeCrud.selById(gatewayTypeId);
      sensor->setType(gatewayType);
    }

    if (param.contains("nodeId")) {
      ID nodeId = param.value("nodeId").value<ID>();
      auto node = nodeCrud.selById(nodeId);
      sensor->setNode(node);
    }

    if (param.contains("serialNumber")) {
      QString serialNumber = param.value("serialNumber").toString();
      sensor->setSerialNumber(serialNumber);
    }

    if (param.contains("comment")) {
      QString comment = param.value("comment").toString();
      sensor->setComment(comment);
    }

    updateSensors << sensor;
  }

  sensorCrud.save(updateSensors);
}

template <template <typename> class Crud>
void Controller<Sensor, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["sensorId"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // SENSORCONTROLLER_H
