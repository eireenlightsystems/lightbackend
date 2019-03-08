#ifndef NODETOJSON_H
#define NODETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<Node>::toJson(const NodeShared& node) const;

} // namespace light

#endif // NODETOJSON_H
