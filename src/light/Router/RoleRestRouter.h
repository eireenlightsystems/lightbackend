#ifndef ROLERESTROUTER_H
#define ROLERESTROUTER_H

#include "Role.h"
#include "RoleController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudRole.h"
#include "RoleToJson.h"

namespace light {

template <>
class RestRouter<Role> : public SimpleEditableRouter<Role>
{
public:
  QString getName() const override {
    return "roles";
  }
};

}

#endif // ROLERESTROUTER_H
