#ifndef ROLERIGHTRESTROUTER_H
#define ROLERIGHTRESTROUTER_H

#include "Roleright.h"
#include "RolerightController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudRoleright.h"
#include "RolerightToJson.h"

namespace light {

template <>
class RestRouter<Roleright> : public SimpleEditableRouter<Roleright>
{
public:
  QString getName() const override {
    return "rolerights";
  }
};

}

#endif // ROLERIGHTRESTROUTER_H
