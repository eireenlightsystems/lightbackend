#include "PostgresCrudSensor.h"

#include "PostgresCrudContract.h"
#include "PostgresCrudContragent.h"
#include "PostgresCrudEquipmentOwner.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudSensorType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> fixtureFields{
    {"id_sensor", "id_sensor", true},
    {"serial_number", "serial_number", false},
    {"comments", "comments_gateway", false},

    {"id_node", "id_node", false},
    {"n_coordinate", "n_coordinate_node", false},
    {"e_coordinate", "e_coordinate_node", false},
    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},

    {"id_contract", "id_contract", false},
    {"code_contract", "code_contract", false},

    {"id_owner", "id_owner", false},
    {"code_owner", "code_owner", false},

    {"id_sensor_type", "id_sensor_type", false},
    {"code_sensor_type", "code_sensor_type", false},
};

PostgresCrud<Sensor>::PostgresCrud() {
  setFields(fixtureFields);
  setView("sensor_pkg_i.sensor_vwf(:id_geograph, :id_owner, :id_sensor_type, :id_contract, :id_node)");
  setInsertSql("select sensor_pkg_i.save(:action, :id_sensor, :id_contract, :id_equipment_type, "
	       ":id_node, :serial_number, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select sensor_pkg_i.del(:id)");
}

Editor<Sensor>::Shared PostgresCrud<Sensor>::parse(const QSqlRecord& record) const {
  auto sensor = SensorShared::create();
  sensor->setId(record.value(getIdAlias()).value<ID>());
  sensor->setComment(record.value(getFieldAlias("comments")).toString());
  sensor->setSerialNumber(record.value(getFieldAlias("serial_number")).toString());

  PostgresCrud<EquipmentOwner> equipmentOwnerCrud;
  sensor->setOwner(equipmentOwnerCrud.parse(record));

  PostgresCrud<Contract> contractCrud;
  sensor->setContract(contractCrud.parse(record));

  PostgresCrud<Node> nodeCrud;
  sensor->setNode(nodeCrud.parse(record));

  PostgresCrud<SensorType> sensorTypeCrud;
  sensor->setType(sensorTypeCrud.parse(record));

  return sensor;
}

BindParamsType PostgresCrud<Sensor>::getSelectParams(const QVariantHash& filters) const {
  return BindParamsType{
      {":id_geograph", filters.value("geographId")},
      {":id_owner", filters.value("ownerId")},
      {":id_sensor_type", filters.value("sensorTypeId")},
      {":id_contract", filters.value("contractId")},
      {":id_node", filters.value("nodeId")},
  };
}

BindParamsType PostgresCrud<Sensor>::getInsertParams(const Editor::Shared& sensor) const {
  return BindParamsType{
      {":action", "ins"},
      {":id_sensor", sensor->getId()},
      {":id_contract", sensor->getContractId()},
      {":id_equipment_type", sensor->getTypeId()},
      {":id_node", sensor->getNodeId()},
      {":serial_number", sensor->getSerialNumber()},
      {":comments", sensor->getComment()},
  };
}

BindParamsType PostgresCrud<Sensor>::getUpdateParams(const Editor::Shared& sensor) const {
  return BindParamsType{
      {":action", "upd"},
      {":id_sensor", sensor->getId()},
      {":id_contract", sensor->getContractId()},
      {":id_equipment_type", sensor->getTypeId()},
      {":id_node", sensor->getNodeId()},
      {":serial_number", sensor->getSerialNumber()},
      {":comments", sensor->getComment()},
  };
}

const QList<Field> sensorContractFields{
    {"id_contract", "id_contract", true},
    {"code_contract", "code_contract", false},
    {"name_contract", "name_contract", false},
};

PostgresCrud<SensorContract>::PostgresCrud() {
  setFields(sensorContractFields);
  setView("sensor_pkg_i.contract_vw");
}

Reader<SensorContract>::Shared PostgresCrud<SensorContract>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contract> contractCrud;
  auto contract = contractCrud.parse(record);
  auto sensorContract = SensorContractShared::create(*contract);
  return sensorContract;
}

const QList<Field> sensorOwnerFields{
    {"id_owner", "id_owner", true},
    {"name_owner", "name_owner", false},
};

PostgresCrud<SensorOwner>::PostgresCrud() {
  setFields(sensorOwnerFields);
  setView("sensor_pkg_i.owner_vw");
}

Reader<SensorOwner>::Shared PostgresCrud<SensorOwner>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setFields({
      {"id_contragent", "id_owner", true},
      {"name", "name_owner", false},
  });
  auto contragent = contragentCrud.parse(record);
  auto sensorOwner = SensorOwnerShared::create(*contragent);
  return sensorOwner;
}

} // namespace PostgresqlGateway
} // namespace light
