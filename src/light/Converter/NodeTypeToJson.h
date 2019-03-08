#ifndef NODETYPETOJSON_H
#define NODETYPETOJSON_H

#include "ToJsonConverter.h"

namespace light {

template <>
QJsonObject ToJsonConverter<NodeType>::toJson(const NodeTypeShared& nodeType) const;

} // namespace light

#endif // NODETYPETOJSON_H
