#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H

#include "typedefs.h"

#include <QDateTime>
#include <QtGlobal>

namespace light {

struct DeviceError
{
  ID gatewayId;
  quint8 nodeNumber;
  quint8 deviceNumber;
  quint8 errorCode;
};
} // namespace light

#endif // SHAREDTYPES_H
