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

template <>
class ToJsonConverter<NodeContract> : public ToJsonConverterTemplate<NodeContract>
{
public:
  QJsonObject toJson(const NodeContractShared& nodeContract) const override;
};

template <>
class ToJsonConverter<NodeOwner> : public ToJsonConverterTemplate<NodeOwner>
{
public:
  QJsonObject toJson(const NodeOwnerShared& nodeOwner) const override;
};

} // namespace light

#endif // NODETOJSON_H
