#ifndef NODETYPETOJSON_H
#define NODETYPETOJSON_H

#include "ToJsonConverter.h"
#include "NodeType.h"

namespace light {

template <>
class ToJsonConverter<NodeType> : public ToJsonConverterTemplate<NodeType>
{
public:
  QJsonObject toJson(const NodeTypeShared& contragent) const override;
};

} // namespace light

#endif // NODETYPETOJSON_H
