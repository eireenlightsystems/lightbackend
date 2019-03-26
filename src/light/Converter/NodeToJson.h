#ifndef NODETOJSON_H
#define NODETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<Node> : public ToJsonConverterTemplate<Node>
{
public:
  QJsonObject toJson(const NodeShared& node) const override;
};

} // namespace light

#endif // NODETOJSON_H
