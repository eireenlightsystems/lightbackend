#ifndef NODERESTROUTER_H
#define NODERESTROUTER_H

#include "NodeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudNodeType.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudGeograph.h"
#include "NodeToJson.h"
#include "NodeTypeToJson.h"

namespace light {

template <>
class RestRouter<Node> : public SimpleEditableRouter<Node>
{
public:
  QString getName() const override {
    return "nodes";
  }
};

template <>
class RestRouter<NodeType> : public SimpleSelectableRouter<NodeType>
{
public:
  QString getName() const override {
    return "nodes-types";
  }
};

} // namespace light

#endif // NODERESTROUTER_H
