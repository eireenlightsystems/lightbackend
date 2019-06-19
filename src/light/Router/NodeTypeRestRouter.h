#ifndef NODETYPERESTROUTER_H
#define NODETYPERESTROUTER_H


#include "NodeType.h"
#include "NodeTypeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudNodeType.h"

namespace light {

template <>
class RestRouter<NodeType> : public SimpleEditableRouter<NodeType>
{
public:
  QString getName() const override {
    return "nodes-types";
  }
};

}

#endif // NODETYPERESTROUTER_H
