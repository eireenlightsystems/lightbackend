#include "PostgresCrudSensorType.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> sensorTypeFields{
    {"id_sensor_type", "id_sensor_type", true},
    {"code_sensor_type", "code_sensor_type", false},
};

PostgresCrud<SensorType>::PostgresCrud() {
  setFields(sensorTypeFields);
  setView("sensor_pkg_i.sensor_type_vw");
}

Reader<SensorType>::Shared PostgresqlGateway::PostgresCrud<SensorType>::parse(const QSqlRecord& record) const {
  auto sensorType = SensorTypeShared::create();
  sensorType->setId(record.value(getIdAlias()).value<ID>());
  sensorType->setCode(record.value(getFieldAlias("code_sensor_type")).toString());
  return sensorType;
}

} // namespace PostgresqlGateway
} // namespace light
