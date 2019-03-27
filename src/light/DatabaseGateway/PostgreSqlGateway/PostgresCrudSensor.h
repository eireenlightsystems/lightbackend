#ifndef POSTGRESCRUDSENSOR_H
#define POSTGRESCRUDSENSOR_H

#include "Sensor.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Sensor> : public Editor<Sensor>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& sensor) const override;
  BindParamsType getUpdateParams(const Shared& sensor) const override;
};

template <>
class PostgresCrud<SensorContract> : public Reader<SensorContract>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDSENSOR_H
