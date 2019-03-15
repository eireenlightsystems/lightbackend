#ifndef GATEWAYTYPEDEF_H
#define GATEWAYTYPEDEF_H

#ifndef IN_MEMORY_DATABASE
#include "PostgresCrud.h"
namespace light {
template <typename T>
using CRUD = PostgresqlGateway::PostgresCrud<T>;
}
#else
#endif

#endif // GATEWAYTYPEDEF_H
