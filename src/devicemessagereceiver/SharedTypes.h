#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H

#include "DeviceMessageReceiverTypeDefs.h"

#include <QDateTime>
#include <QtGlobal>

namespace light {
namespace DeviceMessageReceiver {

struct DeviceError
{
  ID gatewayId;
  quint8 nodeNumber;
  quint8 deviceNumber;
  quint8 errorCode;
};
} // namespace DeviceMessageReceiver
} // namespace light

#endif // SHAREDTYPES_H
