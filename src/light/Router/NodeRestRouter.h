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
  constexpr static const char* path = "node";
};

template <>
class RestRouter<NodeType> : public SimpleSelectableRouter<NodeType>
{
public:
  constexpr static const char* path = "node-type";
};

} // namespace light

#endif // NODERESTROUTER_H
