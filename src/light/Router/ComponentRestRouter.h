#ifndef COMPONENTRESTROUTER_H
#define COMPONENTRESTROUTER_H

#include "Component.h"
#include "ComponentController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudComponent.h"
#include "ComponentToJson.h"

namespace light {

template <>
class RestRouter<Component> : public SimpleEditableRouter<Component>
{
public:
  QString getName() const override {
    return "components";
  }
};

}

#endif // COMPONENTRESTROUTER_H
