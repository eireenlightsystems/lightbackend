#ifndef POSTGRESCRUDEQUIPMENTTYPE_H
#define POSTGRESCRUDEQUIPMENTTYPE_H

#include "EquipmentType.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<EquipmentType> : public Reader<EquipmentType>
{
public:
  PostgresCrud();

protected:
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDEQUIPMENTTYPE_H
