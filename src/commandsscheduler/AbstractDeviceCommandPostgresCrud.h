#ifndef ABSTRACTDEVICECOMMANDPOSTGRESCRUD_H
#define ABSTRACTDEVICECOMMANDPOSTGRESCRUD_H

#include "AbstractDeviceCommand.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<CommandsScheduler::AbstractDeviceCommand> : public Reader<CommandsScheduler::AbstractDeviceCommand>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

}
}

#endif // ABSTRACTDEVICECOMMANDPOSTGRESCRUD_H
