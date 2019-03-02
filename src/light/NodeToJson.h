#ifndef NODETOJSON_H
#define NODETOJSON_H

#include "BaseJsonConverter.h"
#include "typedefs.h"

namespace light {
class NodeToJson : public BaseJsonConverter
{
public:
  NodeToJson() = default;
  ~NodeToJson() override = default;
  void convert(const NodeSharedList & nodes);
};
} // namespace light

#endif // NODETOJSON_H
