#ifndef ABSTRACTNODEGATEWAY_H
#define ABSTRACTNODEGATEWAY_H

#include "typedefs.h"

namespace light {
class AbstractNodeGateway
{
public:
  virtual ~AbstractNodeGateway() = 0;
  virtual NodeShared selectNode(ID id) = 0;
  virtual NodeSharedList selectNodes(const QList<ID>& ids) = 0;
  virtual void saveNode(const NodeShared& node) = 0;
  virtual void saveNodes(const NodeSharedList& nodes) = 0;
  virtual void deleteNode(const NodeShared& node) = 0;
  virtual void deleteNodes(const NodeSharedList& nodes) = 0;
};
} // namespace light

#endif // ABSTRACTNODEGATEWAY_H
