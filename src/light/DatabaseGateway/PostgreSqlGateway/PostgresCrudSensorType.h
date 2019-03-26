#ifndef POSTGRESCRUDSENSORTYPE_H
#define POSTGRESCRUDSENSORTYPE_H

#include "PostgresCrud.h"
#include "SensorType.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<SensorType> : public Reader<SensorType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDSENSORTYPE_H
