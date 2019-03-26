#ifndef NODECHILD_H
#define NODECHILD_H

#include "Equipment.h"
#include "typedefs.h"

namespace light {

class NodeChild : public Equipment
{
public:
  NodeChild() = default;
  ~NodeChild() override = default;

  NodeShared getNode() const;
  ID getNodeId() const;
  void setNode(const NodeShared& value);

  GeographShared getGeograph() const override;

private:
  NodeShared node;
};
} // namespace light

#endif // NODECHILD_H
