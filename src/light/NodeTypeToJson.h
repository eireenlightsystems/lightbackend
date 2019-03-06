#ifndef NODETYPETOJSON_H
#define NODETYPETOJSON_H

#include "BaseJsonConverter.h"
#include "typedefs.h"

namespace light {

class NodeTypeToJson : public BaseJsonConverter
{
public:
  NodeTypeToJson() = default;
  ~NodeTypeToJson() override = default;
  void convert(const NodeTypeSharedList& nodeTypes);
};
} // namespace light

#endif // NODETYPETOJSON_H
