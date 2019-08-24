#ifndef ROLEINCLUDRESTROUTER_H
#define ROLEINCLUDRESTROUTER_H

#include "Roleinclud.h"
#include "RoleincludController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudRoleinclud.h"
#include "RoleincludToJson.h"

namespace light {

template <>
class RestRouter<Roleinclud> : public SimpleEditableRouter<Roleinclud>
{
public:
  QString getName() const override {
    return "roleincluds";
  }
};

}

#endif // ROLEINCLUDRESTROUTER_H
