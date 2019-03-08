#ifndef JSONTOGATEWAYCONVERTER_H
#define JSONTOGATEWAYCONVERTER_H

#include "FromJsonConverter.h"
#include "GatewayController.h"

namespace light {

template<>
GatewayInsertParameters FromJsonConverter<GatewayInsertParameters>::parse(const QJsonObject& jsonObject);

template<>
GatewayUpdateParameters FromJsonConverter<GatewayUpdateParameters>::parse(const QJsonObject& jsonObject);
} // namespace light

#endif // JSONTOGATEWAYCONVERTER_H
