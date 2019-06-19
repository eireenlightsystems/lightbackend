#ifndef POSTGRESCRUDSENSORTYPE_H
#define POSTGRESCRUDSENSORTYPE_H

#include "SensorType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<SensorType> : public Editor<SensorType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDSENSORTYPE_H
