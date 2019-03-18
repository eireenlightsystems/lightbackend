#ifndef NODERESTROUTER_H
#define NODERESTROUTER_H

#include "NodeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudNode.h"
#include "PostgresCrudNodeType.h"
#include "PostgresCrudContract.h"
#include "PostgresCrudGeograph.h"


namespace light {

template <>
class RestRouter<Node> : public SimpleEditableRouter<Node>
{
public:
  constexpr static const char* path = "/api2/node";
};

template <>
class RestRouter<NodeType> : public SimpleSelectableRouter<NodeType>
{
public:
  constexpr static const char* path = "/api2/node-type";
};

} // namespace light

#endif // NODERESTROUTER_H
