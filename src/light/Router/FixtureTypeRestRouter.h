#ifndef FIXTURETYPERESTROUTER_H
#define FIXTURETYPERESTROUTER_H

#include "FixtureType.h"
#include "FixtureTypeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudFixtureType.h"

namespace light {

template <>
class RestRouter<FixtureType> : public SimpleEditableRouter<FixtureType>
{
public:
  QString getName() const override {
    return "fixtures-types";
  }
};

}

#endif // FIXTURETYPERESTROUTER_H
