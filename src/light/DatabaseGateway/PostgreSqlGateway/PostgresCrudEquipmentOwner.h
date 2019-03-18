#ifndef POSTGRESCRUDEQUIPMENTOWNER_H
#define POSTGRESCRUDEQUIPMENTOWNER_H

#include "EquipmentOwner.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<EquipmentOwner> : public Reader<EquipmentOwner>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDEQUIPMENTOWNER_H
