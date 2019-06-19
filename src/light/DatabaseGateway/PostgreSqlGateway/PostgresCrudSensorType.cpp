#include "PostgresCrudSensorType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> sensorTypeFields{
    {"id_equipment_type", "id_sensor_type", true},
    {"code", "code_sensor_type", false},
    {"name", "name_sensor_type", false},
    {"model", "model_sensor_type", false},
    {"comments", "comments_sensor_type", false},
    {"detection_range", "detection_range_sensor_type", false},
};

PostgresCrud<SensorType>::PostgresCrud() {
  setFields(sensorTypeFields);
  setView("sensor_type_pkg_i.sensor_type_vwf()");

  setInsertSql("select sensor_type_pkg_i.save(:action, :id_equipment_type, :code, :name, :model, :comments, :detection_range)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select sensor_type_pkg_i.del(:id)");
}

Reader<SensorType>::Shared PostgresCrud<SensorType>::parse(const QSqlRecord& record) const {
  auto sensorType = SensorTypeShared::create();
  sensorType->setId(record.value(getIdAlias()).value<ID>());
  sensorType->setCode(record.value(getFieldAlias("code")).toString());
  sensorType->setName(record.value(getFieldAlias("name")).toString());
  sensorType->setModel(record.value(getFieldAlias("model")).toString());
  sensorType->setComment(record.value(getFieldAlias("comments")).toString());
  sensorType->setDetectionRange(record.value(getFieldAlias("detection_range")).toDouble());
  return sensorType;
}

BindParamsType PostgresCrud<SensorType>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<SensorType>::getInsertParams(const Editor::Shared &sensorType) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_equipment_type", QVariant()},
      {":code", sensorType->getCode()},
      {":name", sensorType->getName()},
      {":model", sensorType->getModel()},
      {":comments", sensorType->getComment()},
      {":detection_range", sensorType->getDetectionRange()},
  };
}

BindParamsType PostgresCrud<SensorType>::getUpdateParams(const Editor::Shared &sensorType) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_equipment_type", sensorType->getId()},
      {":code", sensorType->getCode()},
      {":name", sensorType->getName()},
      {":model", sensorType->getModel()},
      {":comments", sensorType->getComment()},
      {":detection_range", sensorType->getDetectionRange()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
