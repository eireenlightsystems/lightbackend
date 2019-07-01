#ifndef SUBSTATIONRESTROUTER_H
#define SUBSTATIONRESTROUTER_H

#include "Substation.h"
#include "SubstationController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudSubstation.h"
#include "SubstationToJson.h"

namespace light {

template <>
class RestRouter<Substation> : public SimpleEditableRouter<Substation>
{
public:
  QString getName() const override {
    return "substations";
  }
};

}

#endif // SUBSTATIONRESTROUTER_H
